/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:15:31 by msaadaou          #+#    #+#             */
/*   Updated: 2025/03/13 17:19:55 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_mshel
{
	char    *type;
	char    **cmd_args;
	char    **env;
	// char    *in_redirect;
	// int     is_heredoc;
	// char     *lemiter;
	// char    *out_redirect;
	// int     is_appaned;
	t_redi	*lst;
	int     is_cmd_pipe;
	t_list	**env_var;
	
	struct s_mshel   *left;
	struct s_mshel   *right;
}   t_mshel;

typedef struct s_redi
{
	char    		*redi_file;
	char    		*type;
	int				is_app;
	char			*lemiter;
	struct s_redi   *next;
}	t_redi;


# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "pipex/libft.h"
#endif
