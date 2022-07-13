/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 13:54:57 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/19 17:09:46 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	**ft_mal_free(char **res)
{
	char	**copy_res;

	copy_res = res;
	while (*res)
	{
		free(*res);
		*res = NULL;
		res++;
	}
	free(copy_res);
	copy_res = NULL;
	return (NULL);
}

char	*ft_str_p(char *pr, char const *s, int i, int p_len)
{
	char	*c_pr;

	c_pr = pr;
	while (p_len > 0)
	{
		*pr = s[i - p_len];
		pr++;
		p_len--;
	}
	*pr = '\0';
	return (c_pr);
}

char	**ft_fill_p(char const *s, char c, char **res, int pp_len)
{
	int		i;
	int		p_len;
	char	**c_res;

	i = 0;
	c_res = res;
	while (s[i] && pp_len--)
	{
		p_len = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			p_len++;
		}
		*res = malloc(sizeof(char) * (p_len + 1));
		if (!res)
			return (ft_mal_free(res));
		ft_str_p(*res, s, i, p_len);
		res++;
	}
	return (c_res);
}

int	ft_pp_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (*s != c)
			len++;
		while (*s && *s != c)
			s++;
		if (*s == c && *s)
			s++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		pp_len;

	if (!s)
		return (NULL);
	pp_len = ft_pp_len(s, c);
	res = (char **)malloc(sizeof(char *) * (pp_len + 1));
	if (!res)
		return (NULL);
	res[pp_len] = NULL;
	ft_fill_p(s, c, res, pp_len);
	return (res);
}
