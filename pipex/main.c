/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:15:34 by msaadaou          #+#    #+#             */
/*   Updated: 2025/03/10 17:38:34 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

// t_mshel	*create_node(char *cmd, char type, char **cmd_arg, char **env)
// {
// 	t_mshel	*node;

// 	node = malloc(sizeof(t_mshel));
// 	if (!node)
// 		return (NULL);
// 	node->cmd_args = cmd_arg;
// 	node->type = type;
// 	node->env = env;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// void	open_herdoc(t_mshel *node)
// {
// 	int		new_in_fd;
// 	char	*line;

// 	new_in_fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	// if (new_in_fd == -1)
// 	// 	t_error("pipex: input", data, 1);
// 	line = get_next_line(0);
// 	line[ft_strlen(line) - 1] = 0;
// 	while (ft_strcmp(node->lemiter, line))
// 	{
// 		line[ft_strlen(line)] = '\n';
// 		write(new_in_fd, line, ft_strlen(line));
// 		free(line);
// 		line = get_next_line(0);
// 		line[ft_strlen(line) - 1] = 0;
// 	}
// 	free(line);
// 	close(new_in_fd);
// }

// int execute_command(t_mshel *node, int infd, int outfd, int cs)
// {
// 	int	pid;
// 	int status;

// 	pid = fork();
// 	if (!pid)
// 	{
// 		close(cs);
// 		if (node->in_redirect)
// 		{
// 			if (node->is_heredoc)
// 				open_herdoc(node);
// 			infd = open(node->in_redirect, O_RDONLY);
// 			// if (infd == -1) mn ba3de
// 		}
// 		if (infd)
// 		{
// 			dup2(infd, 0);
// 			close(infd);
// 		}
// 		if (node->out_redirect)
// 		{
// 			if (node->is_appaned)
// 				outfd = open(node->out_redirect, O_CREAT | O_WRONLY | O_APPEND,
// 0644);
// 			else
// 				outfd = open(node->out_redirect, O_CREAT | O_WRONLY | O_TRUNC,
// 0644);
// 		}
// 		if (outfd != 1)
// 		{
// 			dup2(outfd, 1);
// 			close(outfd);
// 		}
// 		char *d = debug_okda(node->env, node->cmd_args[0]);

// 		execve(d, node->cmd_args, node->env);
// 		exit(1);
// 	}
// 	if (!node->is_cmd_pipe)
// 	{
// 		waitpid(pid, &status, 0);
// 		return (WEXITSTATUS(status));
// 	}
// }

// int	execute_tree(t_mshel *node, int fd, int outfd, int closing_pipe)
// {
// 	int		pipe_arr[2];
// 	int		status;

// 	if (!node)
// 		return (1);
// 	if (ft_strncmp(node->type, "pipe", ft_strlen(node->type)))
// 	{
// 		pipe(pipe_arr);
// 		execute_tree(node->left, fd, pipe_arr[1], pipe_arr[0]);
// 		status = execute_tree(node->right, pipe_arr[0], outfd, pipe_arr[1]);
// 		close(pipe_arr[0]);
// 		close(pipe_arr[1]);
// 	}
// 	else if (ft_strncmp(node->type, "&&", ft_strlen(node->type)))
// 	{
// 		status = execute_tree(node->left, fd, outfd, closing_pipe);
// 		if (!status)
// 			execute_tree(node->right, fd, outfd, closing_pipe);
// 	}
// 	else if (ft_strncmp(node->type, "||", ft_strlen(node->type)))
// 	{
// 		status = execute_tree(node->left, fd, outfd, closing_pipe);
// 		if (status)
// 			execute_tree(node->right, fd, outfd, closing_pipe);
// 	}
// 	else if (ft_strncmp(node->type, "cmd", ft_strlen(node->type)))
// 		return (execute_command(node, fd, outfd, closing_pipe));
// 	return (status);
// }

void	get_env(t_list **lst, char **env)
{
	int		i;
	char	**mtr;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		mtr = ft_split(env[i], '=');
		ft_lstadd_back(lst, ft_lstnew(mtr[1], mtr[0]));
		free(mtr);
		i++;
	}
}

void ft_env(t_list *lst)
{
	while (lst)
	{
		printf("%s=%s\n", lst->name, lst->value);
		lst = lst->next;
	}
}

void ft_export(t_list **lst, char *export_param)
{
	char	**mtr;
	char	*value;
	t_list	*temp;
	
	if (!export_param)
	{
		ft_env(*lst);
		return ;
	}
	//validation of mtr[0]
	mtr = ft_split(export_param, '=');
	value = ft_substr(mtr[1], 1, ft_strlen(mtr[1]) - 2);
	free(mtr[1]);
	temp = *lst;
	while (temp)
	{
		if (!ft_strncmp(temp->name, mtr[0], ft_strlen(mtr[0])))
		{
			free(temp->value);
			temp->value = value;
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(lst, ft_lstnew(value, mtr[0]));
}

void	rm_node(t_list *lst, char *str)
{
	t_list	*tmp;
	
	while (lst->next)
	{
		if (!ft_strncmp(lst->next->name, str, ft_strlen(str)))
		{
			tmp = lst->next;
			lst->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		lst = lst->next;
	}
}

void	ft_unset(t_list **lst, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		rm_node(*lst, argv[i]);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_list	*head;
	char *matr[] = {"MESSI", "OLDPWD", "PWD", NULL};
	(void)ac;
	(void)av;
	head = NULL;
	get_env(&head, env);
	ft_export(&head, "MESSI=\"the goat\"");
	printf("\n");
	ft_env (head);
	printf("\n");
	ft_unset(&head, matr);
	ft_env (head);
	return (0);
}
