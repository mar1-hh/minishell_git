/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:34:54 by msaadaou          #+#    #+#             */
/*   Updated: 2025/02/14 21:36:04 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
