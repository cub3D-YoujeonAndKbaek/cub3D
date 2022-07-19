/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:32:09 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/19 21:32:10 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	paint_floor(t_info *info)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < SCHEIGHT / 2)
	{
		j = 0;
		while (j < SCWIDTH)
		{
			color = info->map.celling;
			info->img.buffer[i][j] = color;
			color = info->map.floor;
			info->img.buffer[SCHEIGHT - i - 1][j] = color;
			j++;
		}
		i++;
	}	
}

void	paint_img(t_info *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCHEIGHT)
	{
		x = 0;
		while (x < SCWIDTH)
		{
			info->img.data[y * SCWIDTH + x] = info->img.buffer[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}
