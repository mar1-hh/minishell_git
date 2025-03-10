/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:14:33 by msaadaou          #+#    #+#             */
/*   Updated: 2024/10/28 18:29:13 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	len_prefix(const char *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && is_set(set, s1[i]))
		i++;
	return (i);
}

static size_t	len_sufix(const char *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (is_set(set, s1[i]))
	{
		if (!i)
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	size_t	index_suf;
	size_t	index_pre;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	if (!ft_strlen(s1))
		return (ft_strdup(""));
	index_suf = len_sufix(s1, set);
	index_pre = len_prefix(s1, set);
	size = index_suf - index_pre + 1;
	if (index_pre > index_suf)
		return (ft_strdup(""));
	ptr = malloc(size + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1 + index_pre, size);
	ptr[size] = 0;
	return (ptr);
}
