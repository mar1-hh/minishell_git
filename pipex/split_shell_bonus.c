/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:37:49 by msaadaou          #+#    #+#             */
/*   Updated: 2025/02/08 12:38:32 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	count_word_helper(const char *s)
{
	int	k;

	k = 1;
	while (s[k] == s[0])
		k++;
	return (k);
}

static int	count_words(const char *s)
{
	size_t	i;
	int		flag;
	int		counter;

	i = 0;
	flag = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			if (!flag)
			{
				counter++;
				if (s[i] == '\'' || s[i] == '"')
					i += count_word_helper(s + i);
			}
			flag = 1;
		}
		else
			flag = 0;
		i++;
	}
	return (counter);
}

static void	*free_buffer(char **buffer, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
	return (NULL);
}

static char	*extract_word(char const *str)
{
	int		len;
	int		i;
	char	*word;

	if (is_valide(str))
		return (extract_word_2(str));
	len = 0;
	i = 0;
	while (!(str[len] == ' ') && str[len] != '\0')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_shell(char const *s)
{
	char	**buffer;
	int		i;

	if (!s)
		return (NULL);
	buffer = malloc((count_words(s) + 1) * sizeof(char *));
	if (!buffer)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		if (is_valide(s) || *s != ' ')
		{
			buffer[i] = extract_word(s);
			if (!buffer[i++])
				return (free_buffer(buffer, i - 1));
			if (is_valide(s))
				s += 2;
			s += ft_strlen(buffer[i - 1]);
		}
		else
			s++;
	}
	buffer[i] = NULL;
	return (buffer);
}
