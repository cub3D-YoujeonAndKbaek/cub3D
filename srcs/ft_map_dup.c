/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:43:40 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/12 21:30:54 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	surround_wall_check(t_map *map, char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '0')
			{
				if (i == 0 || j == 0)
					ft_exit("1");
				else if (i == map->height || !str[i][j + 1])
					ft_exit("2");
				else if (str[i][j - 1] == ' ' || str[i][j + 1] == ' ')
					ft_exit("3");
				else if (str[i + 1][j] == ' ' || str[i - 1][j] == ' ')
					ft_exit("4");
			}
			j++;
		}
		i++;
	}
}

void	set_player_pos(t_map *map, char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == 'W' || str[i][j] == 'E' || str[i][j] == 'S'
				|| str[i][j] == 'N')
			{
				map->player.y = i;
				map->player.x = j;
				map->map[(int)i][(int)j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	map_gnl_forward(int fd, t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	while (i < map->start - 1)
	{
		map->ret = ft_get_next_line(fd, &line);
		if (map->ret == -1)
			ft_exit("gnl error");
		free(line);
		line = NULL;
		i++;
	}
}

void	map_set_str(int fd, t_map *map, char **tmp)
{
	int		i;
	char	*line;
	char	*str;

	i = 0;
	while (i < map->height + 1)
	{
		map->ret = ft_get_next_line(fd, &line);
		if (map->ret == -1)
			ft_exit("gnl error");
		str = (char *)malloc(sizeof(char) * (map->width + 1));
		if (!str)
			ft_exit("map_dup malloc error");
		ft_memset(str, ' ', map->width);
		str[map->width] = '\0';
		ft_strcpy(str, line);
		tmp[i] = str;
		free(line);
		line = NULL;
		i++;
	}
}

void	map_dub(char *file_name, t_map *map)
{
	char	**tmp;
	int		fd;

	map->height = map->mcount - map->start;
	tmp = (char **)malloc(sizeof(char *) * (map->height + 2));
	if (!tmp)
		ft_exit("map_dup malloc error");
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_exit("map_dip open error");
	map_gnl_forward(fd, map);
	map_set_str(fd, map, tmp);
	tmp[map->height + 1] = 0;
	map->map = tmp;
	surround_wall_check(map, map->map);
	set_player_pos(map, map->map);
	close(fd);
}
