/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:48:59 by msaadaou          #+#    #+#             */
/*   Updated: 2025/02/15 10:42:36 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	data_finish(t_data *data)
{
	close(data->current_pipe[0]);
	close(data->current_pipe[1]);
	free_matrix(data->matrix_1);
	free_matrix(data->matrix_2);
	free(data->path_1);
	free(data->path_2);
}

void	init_data(t_data *data, char **av, char **envp)
{
	data->matrix_1 = ft_split_shell(av[2]);
	data->matrix_2 = ft_split_shell(av[3]);
	data->path_1 = debug_okda(envp, data->matrix_1[0]);
	data->path_2 = debug_okda(envp, data->matrix_2[0]);
	pipe(data->current_pipe);
}

void	proc_1(t_data *data, char *str, char **envp)
{
	int	new_in_fd;

	close(data->current_pipe[0]);
	if (!data->path_1)
	{
		data_finish(data);
		p_error("command not found", 0);
	}
	new_in_fd = open(str, O_RDONLY);
	if (new_in_fd == -1)
	{
		data_finish(data);
		p_error("pipex: input", 1);
	}
	dup2(new_in_fd, 0);
	close(new_in_fd);
	dup2(data->current_pipe[1], 1);
	close(data->current_pipe[1]);
	execve(data->path_1, data->matrix_1, envp);
	data_finish(data);
	exit(1);
}

void	proc_2(t_data *data, char *str, char **envp)
{
	int	new_out_fd;

	close(data->current_pipe[1]);
	new_out_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!data->path_2)
	{
		data_finish(data);
		p_error("command not found", 0);
	}
	if (new_out_fd == -1)
	{
		data_finish(data);
		p_error("pipex: input", 1);
	}
	dup2(data->current_pipe[0], 0);
	close(data->current_pipe[0]);
	dup2(new_out_fd, 1);
	close(new_out_fd);
	execve(data->path_2, data->matrix_2, envp);
	data_finish(data);
	exit(1);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	pid_t	proc_number_1;
	pid_t	proc_number_2;

	if (ac != 5)
		return (127);
	init_data(&data, av, envp);
	proc_number_1 = fork();
	if (!proc_number_1)
		proc_1(&data, av[1], envp);
	else if (proc_number_1 == -1)
		fork_error(&data);
	proc_number_2 = fork();
	if (!proc_number_2)
		proc_2(&data, av[4], envp);
	else if (proc_number_2 == -1)
		fork_error(&data);
	data_finish(&data);
	waitpid(proc_number_1, NULL, 0);
	waitpid(proc_number_2, &data.n, 0);
	if (WIFEXITED(data.n))
		return (WEXITSTATUS(data.n));
	return (0);
}
