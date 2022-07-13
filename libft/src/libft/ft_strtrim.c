/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:05:35 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/19 17:11:44 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_start_num(char const *s1, char const *set, int start)
{
	while (s1[start])
	{
		if (ft_strchr(set, s1[start]) == 0)
			break ;
		start++;
	}
	return (start);
}

int	ft_end_num(char const *s1, char const *set, int start, int end)
{
	while (end > start)
	{
		if (ft_strchr(set, s1[end - 1]) == 0)
			break ;
		end--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = ft_start_num(s1, set, 0);
	end = ft_end_num(s1, set, start, ft_strlen(s1));
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
