/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:15:31 by msaadaou          #+#    #+#             */
/*   Updated: 2025/03/08 22:49:30 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_

typedef struct s_data
{
    char    type;
    char    *cmd;
    char    **cmd_args;
    char    **env;
    char    *file_redirect;
    struct s_data   *left;
    struct s_data   *right;
}   t_data;

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

#endif