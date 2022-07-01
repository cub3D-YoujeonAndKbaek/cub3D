/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:59:24 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/19 17:04:38 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_len(int nbr)
{
	long long	big_nbr;
	int			i;

	i = 1;
	big_nbr = nbr;
	if (big_nbr < 0)
	{
		i++;
		big_nbr *= -1;
	}
	while (big_nbr > 9)
	{
		big_nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long long	big_nbr;
	int			len;
	char		*res;

	len = ft_len(n);
	big_nbr = n;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		big_nbr *= -1;
	}
	while (big_nbr)
	{
		res[--len] = (big_nbr % 10) + '0';
		big_nbr /= 10;
	}
	return (res);
}
