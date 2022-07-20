/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:33:11 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/20 18:05:19 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	range_number_check(char *line)
{
	int	i;

	i = 0;
	if (!ft_isdigit(*line))
		ft_exit("rgb digit error");
	while (*line)
	{
		if (*line == ',')
		{
			i++;
			line++;
			while (ft_isspace(*line))
				line++;
		}
		if (!ft_isdigit(*line))
			ft_exit("rgb error");
		line++;
	}
	if (i != 2)
		ft_exit("range error");
}

int	set_rgb(char **line)
{
	int	rt;
	int	i;

	rt = ft_atoi(*line);
	i = 1;
	if (rt == 0)
		(*line)++;
	while (rt >= i)
	{
		(*line)++;
		i *= 10;
	}
	while ((**line) && (ft_strncmp(",", (*line), 1) == 0 || ft_isspace(**line)))
		(*line)++;
	return (rt);
}

int	color_check(t_map *map, char *line, char c)
{
	t_range	rgb;

	line += 2;
	while (ft_isspace(*line))
		line++;
	range_number_check(line);
	rgb.r = set_rgb(&line);
	rgb.g = set_rgb(&line);
	rgb.b = set_rgb(&line);
	if (!(rgb.r >= 0 && rgb.r <= 255) || !(rgb.g >= 0 && rgb.g <= 255)
		|| !(rgb.b >= 0 && rgb.b <= 255))
		ft_exit("it is nor 0 ~ 255");
	if (c == 'F' && map->floor == -1)
	{
		map->floor = (rgb.r << 16 | rgb.g << 8 | rgb.b);
	}
	else if (c == 'C' && map->celling == -1)
	{
		map->celling = (rgb.r << 16 | rgb.g << 8 | rgb.b);
	}
	else
		ft_exit("double F or C keyword error");
	return (1);
}

char	*direction_deep_cheak(char *line)
{
	int		fd;
	char	*rt;

	rt = NULL;
	line += 2;
	while (ft_isspace(*line))
		line++;
	fd = open(line, O_RDONLY);
	if (fd == -1)
		ft_exit("texture error");
	close(fd);
	rt = ft_strdup(line);
	return (rt);
}

int	direction_check(t_map *map, char *line, char c)
{
	char	*tmp;

	tmp = direction_deep_cheak(line);
	if (!tmp)
		ft_exit("direction_check error");
	if (c == 'N' && map->no_path == NULL)
		map->no_path = tmp;
	else if (c == 'S' && map->so_path == NULL)
		map->so_path = tmp;
	else if (c == 'W' && map->we_path == NULL)
		map->we_path = tmp;
	else if (c == 'E' && map->ea_path == NULL)
		map->ea_path = tmp;
	else
		ft_exit("double nswe keyword error");
	return (1);
}
