/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:07:41 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/20 15:36:12 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	dda_calc(t_ray *ray, t_map *map)
{
	int	hit;

	hit = 0;
	while (hit != 1)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = X;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = Y;
		}
		if (map->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	if (ray->side == X)
		ray->perpwalldist = ray->sidedist_x - ray->deltadist_x;
	else
		ray->perpwalldist = ray->sidedist_y - ray->deltadist_y;
}

void	set_buff(t_ray *ray, t_img *img, int x)
{
	int		color;
	int		y;

	y = ray->start;
	while (y < ray->end)
	{
		ray->tex_y = (int)ray->texpos & (TEXHEIGHT - 1);
		if (ray->side == X)
		{
			if (ray->raydir_x >= 0)
				color = img->arr_img[E][TEXHEIGHT * ray->tex_y + ray->tex_x];
			else
				color = img->arr_img[W][TEXHEIGHT * ray->tex_y + ray->tex_x];
		}
		else if (ray->side == Y)
		{
			if (ray->raydir_y >= 0)
				color = img->arr_img[S][TEXHEIGHT * ray->tex_y + ray->tex_x];
			else
				color = img->arr_img[N][TEXHEIGHT * ray->tex_y + ray->tex_x];
		}
		img->buffer[y][x] = color;
		ray->texpos += ray->ratio;
		y++;
	}
}

void	mapping_buff(t_ray *ray, t_player *p)
{
	double	wall;

	if (ray->side == X)
		wall = p->pos_y + (ray->perpwalldist * ray->raydir_y);
	else
		wall = p->pos_x + (ray->perpwalldist * ray->raydir_x);
	wall = wall - floor(wall);
	ray->tex_x = (int)(wall * (double)TEXWIDTH);
	if (ray->side == X && ray->raydir_x < 0)
		ray->tex_x = TEXWIDTH - ray->tex_x - 1;
	if (ray->side == Y && ray->raydir_y > 0)
		ray->tex_x = TEXWIDTH - ray->tex_x - 1;
	ray->line_h = (int)(SCHEIGHT / ray->perpwalldist);
	ray->start = SCHEIGHT / 2 - ray->line_h / 2;
	ray->end = SCHEIGHT / 2 + ray->line_h / 2;
	if (ray->start < 0)
		ray->start = 0;
	if (ray->end >= SCHEIGHT)
		ray->end = SCHEIGHT;
	ray->ratio = 1.0 * TEXHEIGHT / ray->line_h;
	ray->texpos = (ray->start - SCHEIGHT / 2 + ray->line_h / 2) * ray->ratio;
}

void	raycasting(t_info *info)
{
	int	x;

	x = 0;
	while (x < SCWIDTH)
	{
		ray_init(info, x);
		dda_calc(&info->ray, &info->map);
		mapping_buff(&info->ray, &info->player);
		set_buff(&info->ray, &info->img, x);
		x++;
	}
}
