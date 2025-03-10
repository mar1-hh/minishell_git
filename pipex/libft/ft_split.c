/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:59:26 by msaadaou          #+#    #+#             */
/*   Updated: 2025/01/11 15:30:58 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 1;
	while (*s)
	{
		if (*s == c)
			flag = 1;
		else if (flag)
		{
			count++;
			flag = 0;
		}
		s++;
	}
	return (count);
}

static void	free_all(char	**res, int i)
{
	while (i >= 0)
	{
		free(res[i]);
		res[i] = NULL;
		i--;
	}
	free(res);
}

static char	**ft_fill(char **arr, char const *s, char c)
{
	int		start;
	int		end;
	int		i;

	start = 0;
	end = 0;
	i = 0;
	while (s[end] && i < count_words(s, c))
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] && s[end] != c)
			end++;
		arr[i] = ft_substr(s, start, end - start);
		if (arr[i] == NULL)
		{
			free_all(arr, i - 1);
			arr = NULL;
			return (arr);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (s == NULL)
		return (NULL);
	arr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr = ft_fill(arr, s, c);
	if (arr == NULL)
		return (NULL);
	return (arr);
}
