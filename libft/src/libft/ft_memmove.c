/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:48:13 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/07 15:07:42 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (s < d && len > 0)
	{
		i = 0;
		while (len - i > 0)
		{
			d[len - 1 - i] = s[len - 1 - i];
			i++;
		}
	}
	else if (s > d && len > 0)
	{
		i = 0;
		while (i < len)
		{
			*d++ = *s++;
			i++;
		}
	}
	return (dst);
}
