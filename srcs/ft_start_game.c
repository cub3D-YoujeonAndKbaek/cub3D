/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:40:31 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/19 15:55:20 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	image_init(t_img *img)
{
	int	i;
	int	j;

	initialization_img(img);
	i = 0;
	while (i < SCHEIGHT)
	{
		j = 0;
		while (j < SCWIDTH)
			img->buffer[i][j++] = 0;
		i++;
	}
	img->arr_img = (int **)malloc(5 * sizeof(int *));
	if (!img->arr_img)
		ft_exit("image_init malloc error");
	i = 0;
	while (i < 5)
	{
		img->arr_img[i] = (int *)malloc(sizeof(int) * texWidth * texHeight);
		if (!img->arr_img[i])
			ft_exit("image_init malloc error");
		ft_memset(img->arr_img[i], 0, (sizeof(int) * texWidth * texHeight));
		i++;
	}
	return (0);
}

void	fill_arr_img(t_info *info, int i)
{
	int	y;
	int	x;

	y = 0;
	while (y < info->img.h)
	{
		x = 0;
		while (x < info->img.w)
		{
			info->img.arr_img[i][info->img.w * y + x] = \
				info->img.data[info->img.h * y + x];
			x++;
		}
		y++;
	}
}

void	image_load(t_info *info)
{
	char	*path;
	int		i;

	i = 1;
	while (i < 5)
	{
		if (i == E)
			path = info->map.ea_path;
		else if (i == W)
			path = info->map.we_path;
		else if (i == S)
			path = info->map.so_path;
		else
			path = info->map.no_path;
		info->img.img = \
			mlx_xpm_file_to_image(info->mlx, path, &info->img.w, &info->img.h);
		if (info->img.w != texWidth || info->img.h != texHeight
			|| info->img.img == NULL)
			ft_exit("image_load xpm file error");
		info->img.data = (int *)mlx_get_data_addr(info->img.img, \
					&info->img.bpp, &info->img.line_size, &info->img.endian);
		fill_arr_img(info, i);
		mlx_destroy_image(info->mlx, info->img.img);
		i++;
	}
}

void	player_init(t_player *pl)
{
	pl->dir_x = 0;
	pl->dir_y = 0;
	if (pl->status == N)
	{
		pl->dir_y = -1;
		pl->plane_x = 0.66;
	}
	else if (pl->status == S)
	{
		pl->dir_y = 1;
		pl->plane_x = -0.66;
	}
	else if (pl->status == W)
	{
		pl->dir_x = -1;
		pl->plane_y = -0.66;
	}
	else
	{
		pl->dir_x = 1;
		pl->plane_y = 0.66;
	}
	pl->move_speed = 0.05;
	pl->rot_speed = 0.05;
}

void	start_game(t_info *info)
{
	info->mlx = mlx_init();
	if (!info->mlx)
		ft_exit("mlx_init() fail\n");
	info->win = mlx_new_window(info->mlx, SCWIDTH, SCHEIGHT, "cub3D");
	if (!info->win)
		ft_exit("init_window fail\n");
	image_init(&info->img);
	image_load(info);
	player_init(&info->player);
	initialization_move(&info->move);
}
