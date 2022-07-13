/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:23:04 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/19 17:11:20 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && len > i)
	{
		j = 0;
		while (haystack[i + j] && haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0' && len > i + j)
				return ((char *)&haystack[i]);
			++j;
		}
		++i;
	}
	return (0);
}
