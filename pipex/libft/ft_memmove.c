/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:46:03 by msaadaou          #+#    #+#             */
/*   Updated: 2024/11/02 12:56:24 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	help(unsigned char *dst, unsigned char *src, size_t len)
{
	while (1)
	{
		--len;
		dst[len] = src[len];
		if (!len)
			break ;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr_2;
	unsigned char	*ptr;
	size_t			i;

	if (dst == src || !len)
		return (dst);
	ptr = (unsigned char *)dst;
	ptr_2 = (unsigned char *)src;
	if (ptr > ptr_2)
		help(ptr, ptr_2, len);
	else
	{
		i = 0;
		while (i < len)
		{
			ptr[i] = ptr_2[i];
			i++;
		}
	}
	return (dst);
}
