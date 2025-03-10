/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:24:37 by msaadaou          #+#    #+#             */
/*   Updated: 2025/02/14 21:41:44 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	*helper_path(char *str, char *cmd, int size)
{
	char	*complete_path;
	char	**commands_path;

	complete_path = ft_substr(str, size, ft_strlen(str) - size);
	if (!complete_path)
		return (NULL);
	commands_path = ft_split(complete_path, ':');
	if (!commands_path)
	{
		free(complete_path);
		return (NULL);
	}
	free(complete_path);
	return (helper_path_cmd(commands_path, cmd));
}

void	fork_fail(t_pip *data, int i)
{
	data_finish(data);
	close_pipes(data, i);
	exit(1);
}

char	*debug_okda(char **env, char *cmd)
{
	char	*str;
	char	*cmdr;
	int		i;

	if (!cmd)
		return (NULL);
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	cmdr = ft_strjoin("/", cmd);
	if (!cmdr)
		return (NULL);
	i = 0;
	while (env[i])
	{
		str = ft_strnstr(env[i], "PATH=", ft_strlen("PATH="));
		if (str)
			return (helper_path(str, cmdr, ft_strlen("PATH=")));
		i++;
	}
	return (NULL);
}

void	t_error(char *str, t_pip *data, int status)
{
	data_finish(data);
	perror(str);
	exit(status);
}
