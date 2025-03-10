/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:36:34 by msaadaou          #+#    #+#             */
/*   Updated: 2025/02/12 15:50:49 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	middle_proc(t_pip *data, int i, char **env)
{
	data[i].n = fork();
	if (!data[i].n)
	{
		if (!data[i].path)
			t_error("command not found", data, 127);
		close_pipes(data, i + 1);
		close(data[i - 1].pip[WRITE]);
		close(data[i].pip[READ]);
		dup2(data[i - 1].pip[READ], 0);
		close(data[i - 1].pip[READ]);
		dup2(data[i].pip[WRITE], 1);
		close(data[i].pip[WRITE]);
		execve(data[i].path, data[i].matrix, env);
		data_finish(data);
		exit(1);
	}
	else if (data[i].n == -1)
		fork_fail(data, data->cmds_size);
}

void	process_handle(t_pip *data, char **av, int ac, char **envp)
{
	int	i;

	i = 0;
	while (i < data->cmds_size)
	{
		if (!i)
			proc_1(data, av, envp);
		else if (i == data->cmds_size - 1)
			proc_finale(data, av, envp, ac);
		else
			middle_proc(data, i, envp);
		if (i)
		{
			close(data[i - 1].pip[READ]);
			close(data[i - 1].pip[WRITE]);
		}
		i++;
	}
}

void	init_data(t_pip *data, int ac, char **av, char **envp)
{
	int	i;
	int	flag;

	flag = 2;
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		flag++;
	i = 0;
	while (i < ac - (flag + 1))
	{
		data[i].matrix = ft_split_shell(av[i + flag]);
		if (!data[i].matrix)
			finish_n_data(data, i);
		data[i].path = debug_okda(envp, data[i].matrix[0]);
		if (pipe(data[i].pip) == -1)
			finish_n_data(data, i);
		data[i].cmds_size = ac - (flag + 1);
		i++;
	}
}

int	ft_strcmp(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] || str2[i])
	{
		if (str[i] > str2[i])
			return (1);
		else if (str[i] < str2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	close_pipes(t_pip *data, int i)
{
	while (i < data->cmds_size)
	{
		close(data[i].pip[0]);
		close(data[i].pip[1]);
		i++;
	}
}
