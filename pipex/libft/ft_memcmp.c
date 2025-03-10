/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:49:07 by msaadaou          #+#    #+#             */
/*   Updated: 2024/10/28 16:42:40 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptr_2;

	i = 0;
	ptr = (unsigned char *)s1;
	ptr_2 = (unsigned char *)s2;
	while (i < n)
	{
		if (ptr[i] > ptr_2[i])
			return (ptr[i] - ptr_2[i]);
		else if (ptr[i] < ptr_2[i])
			return (ptr[i] - ptr_2[i]);
		i++;
	}
	return (0);
}
