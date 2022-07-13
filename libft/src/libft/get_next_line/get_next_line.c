/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:38:55 by kbaek             #+#    #+#             */
/*   Updated: 2021/09/19 18:20:44 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

int	ft_d(char *content, char **st)
{
	if (*st)
	{
		free(*st);
		*st = content;
	}
	return (1);
}

int	ft_trim(char **st, char **line, int nl, int i)
{
	char	*tmp;

	if (nl == 0)
		*line = ft_strdup("");
	else
	{
		*line = ft_calloc(sizeof(char *), nl + 1);
		while ((*st)[i] && nl--)
		{
			(*line)[i] = (*st)[i];
			i++;
		}
		(*line)[i] = '\0';
	}
	if (!((*st)[i + 1]))
		return (ft_d(NULL, &*st));
	tmp = ft_calloc(sizeof(char), ft_strlen(*st) - nl);
	nl = 0;
	while ((*st)[++i])
		tmp[nl++] = (*st)[i];
	tmp[nl] = '\0';
	return (ft_d(tmp, &*st));
}

int	ft_last_line_trim(char **st, char **line, int s_n)
{
	if (s_n == -1)
		return (ft_error(&*st));
	if (!*st)
	{
		*line = ft_strdup("");
		return (0);
	}
	s_n = chk_enter(*st);
	if (s_n >= 0)
		return (ft_trim(&*st, &*line, s_n, 0));
	else
	{
		*line = malloc(ft_strlen(*st) + 1);
		if (!line)
			return (ft_error(&*st));
		s_n = 0;
		while ((*st)[s_n] && (((*st)[s_n + 1] != '\n')))
		{
			(*line)[s_n] = (*st)[s_n];
			s_n++;
		}
		(*line)[s_n] = '\0';
		ft_d(NULL, &*st);
	}
	return (0);
}

char	*ft_st(char **st, char **buf)
{
	char	*tmp;

	if (!*st)
		tmp = ft_strdup(*buf);
	else
		tmp = ft_gnl_strjoin(*st, *buf);
	if (tmp == NULL)
		free(*buf);
	return (tmp);
}

int	ft_get_next_line(int fd, char **line)
{
	static char	*st[OPEN_MAX];
	char		*buf;
	int			size;

	if (fd < 0 || fd >= OPEN_MAX || !line || BUFFER_SIZE < 1)
		return (-1);
	buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	size = read(fd, buf, BUFFER_SIZE);
	while (size > 0)
	{
		buf[size] = '\0';
		st[fd] = ft_st(&st[fd], &buf);
		if (st[fd] == NULL)
			return (ft_error(&*st));
		size = chk_enter(st[fd]);
		if (size >= 0)
		{
			free(buf);
			return (ft_trim(&st[fd], line, size, 0));
		}
	}
	free(buf);
	return (ft_last_line_trim(&st[fd], line, size));
}
