/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:15:34 by msaadaou          #+#    #+#             */
/*   Updated: 2025/03/08 23:48:32 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*create_node(char *cmd, char type, char **cmd_arg, char **env)
{
	t_data	*node;

	node = malloc(sizeof(t_data));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->cmd_args = cmd_arg;
	node->type = type;
	node->env = env;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void execute_command(t_data *node, int infd, int outfd, int cs)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		close(cs);
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
		execve(node->cmd, node->cmd_args, node->env);
		exit(1);
	}
}

void	execute_tree(t_data *node, int fd, int outfd, int closing_pipe)
{	
	int		pipe_arr[2];
	
	if (!node)
		return ;
	if (node->type == '|')
	{
		pipe(pipe_arr);
		execute_tree(node->left, fd, pipe_arr[1], pipe_arr[0]);
		execute_tree(node->right, pipe_arr[0], outfd, pipe_arr[1]);
		close(pipe_arr[0]);
		close(pipe_arr[1]);
	}
	else if (node->cmd)
		execute_command(node, fd, outfd, closing_pipe);
}


int main(int ac, char **av, char **env)
{
	t_data	*root;
	char *matr1[] = {"ls", NULL};
	char *matr2[] = {"grep","a.out", NULL};
    char *matr3[] = {"cat", "-e", NULL};

	root = create_node(NULL, '|', NULL, env);
    root->left = create_node(NULL, '|', NULL, env);
    root->right = create_node("/usr/bin/cat", 'c', matr3, env);


	root->left->left = create_node("/bin/ls", 'c', matr1, env);
	root->left->right = create_node("/usr/bin/grep", 'c', matr2, env);
	execute_tree(root, 0, 1, -1);
	wait(NULL);
	wait(NULL);
    wait(NULL);
	return (0);
}
