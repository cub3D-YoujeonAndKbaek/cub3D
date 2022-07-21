/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:43:42 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/20 18:05:05 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	map_check(t_map *map, t_player *p, char *line)
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
			if (p->status != 0)
				ft_exit("its more than one player error");
			p->status = set_player_dir(c);
		}
		i++;
	}
	if (map->width < i)
		map->width = i;
	if (map->start == 0)
		map->start = map->mcount;
}

int	file_check(t_map *map, t_player *p, char *line)
{
	int	i;
	int	rt;

	i = 0;
	rt = 0;
	if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3)
		|| !ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3))
		rt = direction_check(map, line, line[0]);
	else if (!ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2))
		rt = color_check(map, line, line[0]);
	else if (line[0] == 0)
		rt = 1;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '0' || line[i] == '1')
	{
		if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path
			|| (map->floor == -1) || (map->celling == -1))
			ft_exit("something missing or file order is worng");
		map_check(map, p, line);
		rt = 1;
	}
	return (rt);
}

void	file_parsing(char *file_name, t_info *info)
{
	char	*line;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_exit("file open error\n");
	initialization_map(&info->map);
	info->player.status = 0;
	while (info->map.ret == 1)
	{
		info->map.ret = ft_get_next_line(fd, &line);
		if (info->map.ret == -1)
			ft_exit("gnl error");
		info->map.mcount += 1;
		if (file_check(&info->map, &info->player, line) == 0)
			ft_exit("wrong keyword inside error");
		free(line);
		line = NULL;
	}
	map_dub(file_name, info);
	close(fd);
	info->map.ret = 1;
}
