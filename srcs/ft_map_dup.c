/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:28:10 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/19 21:42:38 by kbaek            ###   ########.fr       */
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
				if (i == 0 || j == 0 || i == map->height || !str[i][j + 1])
					ft_exit("surround_wall_check no wall first or last");
				else if (str[i][j - 1] == ' ' || str[i][j + 1] == ' ')
					ft_exit("surround_wall_check no wall left or right");
				else if (str[i + 1][j] == ' ' || str[i - 1][j] == ' ')
					ft_exit("surround_wall_check no wall up or down");
			}
			j++;
		}
		i++;
	}
}

void	set_player_pos(t_player *p, char **str)
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
				p->pos_y = i + 0.5;
				p->pos_x = j + 0.5;
				str[(int)i][(int)j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	map_gnl_forward(int fd, t_info *info)
{
	int		i;
	char	*line;

	i = 0;
	while (i < info->map.start - 1)
	{
		info->map.ret = ft_get_next_line(fd, &line);
		if (info->map.ret == -1)
			ft_exit("gnl error");
		free(line);
		line = NULL;
		i++;
	}
}

void	map_set_str(int fd, t_info *info, char **tmp)
{
	int		i;
	char	*line;
	char	*str;

	i = 0;
	while (i < info->map.height + 1)
	{
		info->map.ret = ft_get_next_line(fd, &line);
		if (info->map.ret == -1)
			ft_exit("gnl error");
		str = (char *)malloc(sizeof(char) * (info->map.width + 1));
		if (!str)
			ft_exit("map_dup malloc error");
		ft_memset(str, ' ', info->map.width);
		str[info->map.width] = '\0';
		ft_strcpy(str, line);
		tmp[i] = str;
		free(line);
		line = NULL;
		i++;
	}
}

void	map_dub(char *file_name, t_info *info)
{
	char	**tmp;
	int		fd;

	info->map.height = info->map.mcount - info->map.start;
	tmp = (char **)malloc(sizeof(char *) * (info->map.height + 2));
	if (!tmp)
		ft_exit("map_dup malloc error");
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_exit("map_dip open error");
	map_gnl_forward(fd, info);
	map_set_str(fd, info, tmp);
	tmp[info->map.height + 1] = 0;
	info->map.map = tmp;
	surround_wall_check(&info->map, info->map.map);
	set_player_pos(&info->player, info->map.map);
	close(fd);
}
