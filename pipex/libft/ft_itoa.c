/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:25:02 by msaadaou          #+#    #+#             */
/*   Updated: 2024/10/28 13:35:29 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*help(char *ptr, int n, int size, int flag)
{
	ptr[size--] = 0;
	while (size >= 0)
	{
		ptr[size--] = n % 10 + '0';
		n /= 10;
	}
	if (flag)
		ptr[0] = '-';
	return (ptr);
}

static int	number_len(int n)
{
	int	counter;

	if (!n)
		return (1);
	counter = 0;
	while (n)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	int		flag;

	ptr = NULL;
	flag = 0;
	size = number_len(n);
	if (!n)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		size++;
		flag = 1;
		n *= -1;
	}
	ptr = malloc(size + 1);
	if (!ptr)
		return (NULL);
	return (help(ptr, n, size, flag));
}
