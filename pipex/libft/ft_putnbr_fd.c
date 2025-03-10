/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:23:13 by msaadaou          #+#    #+#             */
/*   Updated: 2024/10/29 12:39:06 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbl;

	if (fd < 0)
		return ;
	nbl = n;
	if (nbl < 0)
	{
		ft_putchar_fd('-', fd);
		nbl *= -1;
	}
	if (nbl > 9)
		ft_putnbr_fd(nbl / 10, fd);
	ft_putchar_fd(nbl % 10 + 48, fd);
}
