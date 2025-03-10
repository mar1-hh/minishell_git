/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:21:16 by msaadaou          #+#    #+#             */
/*   Updated: 2025/02/15 10:32:42 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_herdoc(char **av, t_pip *data)
{
	int		new_in_fd;
	char	*line;

	new_in_fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (new_in_fd == -1)
		t_error("pipex: input", data, 1);
	line = get_next_line(0);
	line[ft_strlen(line) - 1] = 0;
	while (ft_strcmp(av[2], line))
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

void	proc_1(t_pip *data, char **av, char **envp)
{
	int	new_in_fd;

	data->n = fork();
	if (!data->n)
	{
		if (!data->path)
			t_error("command not found", data, 127);
		close_pipes(data, 1);
		if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
			open_herdoc(av, data);
		close(data->pip[READ]);
		new_in_fd = open(av[1], O_RDONLY);
		if (new_in_fd == -1)
			t_error("pipex: input", data, 1);
		dup2(new_in_fd, 0);
		close(new_in_fd);
		dup2(data->pip[WRITE], 1);
		close(data->pip[WRITE]);
		execve(data->path, data->matrix, envp);
		data_finish(data);
		free(data);
		exit(1);
	}
	else if (data->n == -1)
		fork_fail(data, 0);
}

void	proc_finale(t_pip *data, char **av, char **envp, int ac)
{
	int	new_out_fd;

	data[data->cmds_size - 1].n = fork();
	if (!data[data->cmds_size - 1].n)
	{
		dup2(data[data->cmds_size - 2].pip[READ], 0);
		close_pipes(data, data->cmds_size - 2);
		if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
			new_out_fd = open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			new_out_fd = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (new_out_fd == -1)
			t_error("pipex: input", data, 1);
		dup2(new_out_fd, 1);
		close(new_out_fd);
		if (!data[data->cmds_size - 1].path)
			t_error("command not found", data, 127);
		execve(data[data->cmds_size - 1].path, data[data->cmds_size - 1].matrix,
			envp);
		data_finish(data);
		exit(1);
	}
	else if (data[data->cmds_size - 1].n == -1)
		fork_fail(data, data->cmds_size);
}

void	data_finish(t_pip *data)
{
	int	i;

	i = 0;
	while (i < data[0].cmds_size)
	{
		free(data[i].path);
		free_matrix(data[i].matrix);
		i++;
	}
	free(data);
}

int	main(int ac, char **av, char **envp)
{
	t_pip	*data;
	int		exit_st;
	int		i;
	int		size;

	valide_parametre(ac, av, &size);
	data = malloc((size) * sizeof(t_pip));
	if (!data)
		return (1);
	init_data(data, ac, av, envp);
	process_handle(data, av, ac, envp);
	i = data->cmds_size - 1;
	waitpid(data[i].n, &exit_st, 0);
	i = 0;
	while (i < data[0].cmds_size - 1)
	{
		waitpid(data[i].n, NULL, 0);
		i++;
	}
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		unlink(av[1]);
	data_finish(data);
	if (WIFEXITED(exit_st))
		return (WEXITSTATUS(exit_st));
	return (0);
}
