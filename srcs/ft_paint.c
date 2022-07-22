/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:32:09 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/23 00:04:07 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	paint_floor(t_info *info)
{
	int	i;
	int	j;
	int	celling;
	int	floor;

	i = 0;
	celling = info->map.celling;
	floor = info->map.floor;
	while (i < SCHEIGHT / 2)
	{
		j = 0;
		while (j < SCWIDTH)
		{
			info->img.buffer[i][j] = celling;
			info->img.buffer[SCHEIGHT - i - 1][j] = floor;
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
