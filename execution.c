/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:11:14 by msaadaou          #+#    #+#             */
/*   Updated: 2025/03/17 14:42:45 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	open_herdoc(t_redirection *node)
{
	int		new_in_fd;
	char	*line;

	new_in_fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// if (new_in_fd == -1)
	// 	t_error("pipex: input", data, 1);
	line = get_next_line(0);
	line[ft_strlen(line) - 1] = 0;
	while (ft_strcmp(node->file, line))
	{
		line[ft_strlen(line)] = '\n';
		write(new_in_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
		line[ft_strlen(line) - 1] = 0;
	}
	free(line);
	close(new_in_fd);
}

void	handle_redirection(t_ast_node *node, int *infd, int *outfd)
{
	t_redirection	*lst;

	lst = node->redirections;
	while (lst)
	{
		if (lst->type == TOKEN_REDIR_IN)
		{
			*infd = open(lst->file, O_RDONLY);
			if (infd == -1)
			{
				perror("open");
				return ;
			}
		}
		else if (lst->type == TOKEN_APPEND || lst->type == TOKEN_REDIR_OUT)
		{
			if (lst->type == TOKEN_APPEND)
				*outfd = open(lst->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
			else
				*outfd = open(lst->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (*outfd == -1)
			{
				perror("open");
				return ;
			}
		}
		else if (lst->type == TOKEN_HEREDOC)
		{
			open_herdoc(lst);
			*infd = open("here_doc", O_RDONLY);
			if (*outfd == -1)
			{
				perror("open");
				return ;
			}
		}
		lst = lst->next;
	}
}

// int my_execve(t_ast_node *node)
// {
// 	if (!ft_strcmp(node->cmd_args[0], "echo"))
// 		return (ft_echo(node->cmd_args));
// 	else if (!ft_strcmp(node->cmd_args[0], "cd"))
// 		return (ft_cd(node->env_var, node->cmd_args[1]));
// 	else if (!ft_strcmp(node->cmd_args[0], "pwd"))
// 		return (ft_pwd());
// 	else if (!ft_strcmp(node->cmd_args[0], "export"))
// 		return (ft_export(node->env_var, node->cmd_args[1]));
// 	else if (!ft_strcmp(node->cmd_args[0], "unset"))
// 		return (ft_unset(node->env_var, node->cmd_args));
// 	else if (!ft_strcmp(node->cmd_args[0], "env"))
// 		return (ft_env(*(node->env_var)));
// 	// else if (!ft_strcmp(node->cmd_args[0], "exit")) to do
// 	// 	return (1);
// }

// int execute_builtin(t_ast_node *node, int infd, int outfd)
// {
// 	handle_redirection(node, &infd, &outfd);
// 	if (infd)
// 	{
// 		dup2(infd, 0);
// 		close(infd);
// 	}
// 	if (outfd != 1)
// 	{
// 		dup2(outfd, 1);
// 		close(outfd);
// 	}
// 	my_execve(node);
// }

// int	is_builtin(char *cmd)
// {
// 	if (!ft_strcmp(cmd, "echo"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "cd"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "pwd"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "export"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "unset"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "env"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "exit"))
// 		return (1);
// 	return (0);
// }

int execute_command(t_ast_node *node, int infd, int outfd, int cs)
{
	int	pid;
	int status;
	
	// if (is_builtin(node->args[0]))
	// 	execute_builtin(node, infd, outfd);
	pid = fork();
	if (!pid)
	{
		close(cs);
		handle_redirection(node, &infd, &outfd);
		if (infd)
		{
			dup2(infd, 0);
			close(infd);
		}
		if (outfd != 1)
		{
			dup2(outfd, 1);
			close(outfd);
		}
		char *d = debug_okda(node->env, node->args[0]);

		execve(d, node->args, node->env);
		exit(1);
	}
	if (node->is_wait)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (10);
}

int	execute_tree(t_ast_node *node, int fd, int outfd, int closing_pipe)
{
	int		pipe_arr[2];
	int		status;

	if (!node)
		return (1);
	if (node->type == AST_PIPE)
	{
		pipe(pipe_arr);
		execute_tree(node->left, fd, pipe_arr[1], pipe_arr[0]);
		status = execute_tree(node->right, pipe_arr[0], outfd, pipe_arr[1]);
		close(pipe_arr[0]);
		close(pipe_arr[1]);
	}
	else if (node->type == AST_AND)
	{
		status = execute_tree(node->left, fd, outfd, closing_pipe);
		if (!status)
			status = execute_tree(node->right, fd, outfd, closing_pipe);
	}
	else if (node->type == AST_OR)
	{
		status = execute_tree(node->left, fd, outfd, closing_pipe);
		if (status)
			status = execute_tree(node->right, fd, outfd, closing_pipe);
	}
	else if (node->type == AST_CMD)
		return (execute_command(node, fd, outfd, closing_pipe));
	return (status);
}
