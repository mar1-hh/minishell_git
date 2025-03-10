/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:41:46 by msaadaou          #+#    #+#             */
/*   Updated: 2024/11/02 09:39:04 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptr_2;

	if (!n || (dst == src))
		return (dst);
	i = 0;
	ptr = (unsigned char *)dst;
	ptr_2 = (unsigned char *)src;
	while (i < n)
	{
		ptr[i] = ptr_2[i];
		i++;
	}
	return (dst);
}
