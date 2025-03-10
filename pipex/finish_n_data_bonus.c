/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_n_data_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:46:45 by msaadaou          #+#    #+#             */
/*   Updated: 2025/02/14 22:44:41 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	finish_n_data(t_pip *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (data[i].matrix)
			free_matrix(data[i].matrix);
		if (data[i].path)
			free(data[i].path);
		close(data[i].pip[0]);
		close(data[i].pip[1]);
		i++;
	}
	exit(1);
}

char	*helper_path_cmd(char **commands_path, char *cmd)
{
	int		i;
	char	*command_path;

	i = 0;
	while (commands_path[i])
	{
		command_path = ft_strjoin(commands_path[i], cmd);
		if (!command_path)
		{
			free_matrix(commands_path);
			free(cmd);
			return (NULL);
		}
		if (!access(command_path, X_OK))
		{
			free_matrix(commands_path);
			free(cmd);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	free_matrix(commands_path);
	free(cmd);
	return (NULL);
}

void	valide_parametre(int ac, char **av, int *size)
{
	if (ac < 5)
		exit(127);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) && ac < 6)
		exit(127);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		*size = ac - 4;
	else
		*size = ac - 3;
}
