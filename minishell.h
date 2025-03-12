/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:15:31 by msaadaou          #+#    #+#             */
/*   Updated: 2025/03/12 18:03:59 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_mshel
{
	char    *type;
	char    **cmd_args;
	char    **env;
	char    *in_redirect;
	int     is_heredoc;
	char     *lemiter;
	char    *out_redirect;
	int     is_appaned;
	int     is_cmd_pipe;
	t_list	**env_var;
	struct s_mshel   *left;
	struct s_mshel   *right;
}   t_mshel;

// typedef struct s_list
// {
// 	char    		*name;
// 	char    		*value;
// 	struct s_list   *next;
// }	t_env;


# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "pipex/libft.h"
#endif
