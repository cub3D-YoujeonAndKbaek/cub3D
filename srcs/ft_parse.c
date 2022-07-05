/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:43:42 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/05 21:51:57 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	direction_deep_cheak(t_map *map, char *line, char **tmp)
{
	int	fd;

	line += 2;
	while (ft_isspace(*line))
		line++;
	fd = open(line, O_RDONLY);
	if (fd == -1)
		ft_exit("texture errer");
	close(fd);
	*tmp = ft_strdup(line);
}

void	direction_check(t_map *map, char *line, char c)
{
	char	*tmp;

	if (c == 'N')
	{
		if (direction_deep_cheak(map, line, &tmp))
			map->no_path = tmp;
	}
	else if (c == 'S')
	{
		if (direction_deep_cheak(map, line, &tmp))
			map->so_path = tmp;
	}
	else if (c == 'W')
	{
		if (direction_deep_cheak(map, line, &tmp))
			map->we_path = tmp;
	}
	else if (c == 'E')
	{
		if (direction_deep_cheak(map, line, &tmp))
			map->ea_path = tmp;
	}
}

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
	while (rt > i)
	{
		(*line)++;
		i *= 10;
	}
	while ((**line) && (!ft_strncmp(",", (*line), ft_strlen(*line))
			|| ft_isspace(**line)))
		(*line)++;
	return (rt);
}

void	color_check(t_map *map, char *line, char c)
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
	if (c == 'F')
	{
		map->floor = (rgb.r << 16 | rgb.g << 8 | rgb.b);
	}
	else if (c == 'C')
	{
		map->celling = (rgb.r << 16 | rgb.g << 8 | rgb.b);
	}
}

int	set_player_dir(char c)
{
	if (c == 'W')
		return (W);
	else if (c == 'N')
		return (N);
	else if (c == 'S')
		return (S);
	else if (c == 'E')
		return (E);
	return (0);
}

void	map_check(t_map *map, char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		c = line[i];
		if (!(c == ' ') && c != '0' && c != '1' && c != 'W'
			&& c != 'N' && c != 'S' && c != 'E')
			ft_exit("map argv error");
		else if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
		{
			if (map->player.status != 0)
				ft_exit("its more than one player error");
			map->player.status = set_player_dir(c);
		}
		i++;
	}
	if (map->width < i)
		map->width = i;
	if (map->start == 0)
		map->start = map->mcount;
}

void	file_check(t_map *map, char *line)
{
	int	i;

	if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3)
		|| !ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3))
		direction_check(map, line, line[0]);
	else if (!ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2))
		color_check(map, line, line[0]);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '0' || line[i] == '1')
	{
		if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path
			|| (map->floor == -1) || (map->celling == -1))
			ft_exit("something missing or file order is worng");
		map_check(map, line);
	}
}

void	file_parsing(char *file_name, t_map *map)
{
	char	*line;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_exit("file open error\n");
	initialization_map(map);
	while (map->ret == 1)
	{
		map->ret = ft_get_next_line(fd, &line);
		if (map->ret == -1)
			ft_exit("error");
		map->mcount += 1;
		file_check(map, line);
		free(line);
		line = NULL;
	}
	map_dub(file_name, map);
	print_struct(map);
	close (fd);
	map->ret = 1;
	//ft_fill_map(line, map, file_name);
}
