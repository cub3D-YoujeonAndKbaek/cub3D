/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:47:40 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/19 17:08:37 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	big_n;

	big_n = n;
	if (big_n < 0)
	{
		ft_putchar_fd('-', fd);
		big_n *= -1;
	}
	if (big_n >= 10)
	{
		ft_putnbr_fd(big_n / 10, fd);
		ft_putnbr_fd(big_n % 10, fd);
	}
	else
	{
		ft_putchar_fd(big_n + '0', fd);
	}
}
