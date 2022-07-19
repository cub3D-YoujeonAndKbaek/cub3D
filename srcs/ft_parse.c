/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:43:42 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/19 15:55:07 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

void	file_check(t_map *map, t_player *p, char *line)
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
		map_check(map, p, line);
	}
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
			ft_exit("error");
		info->map.mcount += 1;
		file_check(&info->map, &info->player, line);
		free(line);
		line = NULL;
	}
	map_dub(file_name, info);
	close (fd);
	info->map.ret = 1;
}
