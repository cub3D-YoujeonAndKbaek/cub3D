/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 21:36:57 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/16 19:27:23 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	int		i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	free(s1);
	while (*s2)
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	chk_enter(char *st)
{
	int		i;

	i = 0;
	while (st[i])
	{
		if (st[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_error(char **st)
{
	if (*st)
		free(*st);
	return (-1);
}
