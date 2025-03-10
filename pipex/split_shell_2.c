/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:29:16 by msaadaou          #+#    #+#             */
/*   Updated: 2025/02/07 22:31:47 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*extract_word_2(char const *str)
{
	int		len;
	int		i;
	char	*word;

	len = 1;
	i = 0;
	while (!(str[len] == str[0]) && str[len] != '\0')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i + 1 < len)
	{
		word[i] = str[i + 1];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	is_valide(const char *s)
{
	char	c;

	if (!(*s == '\'' || *s == '"'))
		return (0);
	c = *s++;
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}
