/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:25:26 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/07 15:07:42 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*p;
	char	*d;

	len = ft_strlen(s1);
	p = malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	d = p;
	while (len--)
	{
		*p = *s1;
		p++;
		s1++;
	}
	*p = '\0';
	return (d);
}
