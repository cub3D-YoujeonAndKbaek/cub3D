/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:38:50 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/19 17:10:29 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	s_d;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	s_d = dstsize - d_len;
	if (dstsize == 0)
		return (s_len);
	if (dstsize <= d_len)
		return (s_len + dstsize);
	while (*dst)
		dst++;
	while (--s_d && *src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (d_len + s_len);
}
