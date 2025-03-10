/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:32:41 by msaadaou          #+#    #+#             */
/*   Updated: 2025/01/16 13:23:11 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, ft_strlen(s1) + 1);
	ft_strlcat(ptr, s2, size);
	return (ptr);
}
