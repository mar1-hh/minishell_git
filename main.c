/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:15:34 by msaadaou          #+#    #+#             */
/*   Updated: 2025/03/08 23:05:48 by msaadaou         ###   ########.fr       */
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
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void command_pipe(t_data *node, int infd, int outfd)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		if (infd)
		{
			dup2(infd, 0);
			close(infd);
		}
		if (outfd != -1)
		{
			dup2(outfd, 1);
			close(outfd);
		}
		execve(node->cmd, node->cmd_args, node->env);
		exit(1);
	}
}

void	execute_tree(t_data *node, int fd, int outfd)
{	
	int		pipe_arr[2];
	
	if (!node)
		return (NULL);
	if (node->type == '|')
	{
		pipe(pipe_arr);
		execute_tree(node->left, fd, pipe_arr[1]);
		execute_tree(node->right, pipe_arr[0], -1);
		close(pipe_arr[0]);
		close(pipe_arr[1]);
	}
	else if (node->cmd)
		command_pipe(node, fd, outfd);
}


int main(int ac, char **av, char **env)
{

	
	return (0);
}