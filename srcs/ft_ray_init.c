/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:25:25 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/20 15:36:10 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	sidedist_init(t_ray *ray, t_player *p)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (p->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - p->pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (p->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - p->pos_y) * ray->deltadist_y;
	}
}

void	ray_init(t_info *info, int x)
{
	double	camera;

	camera = 2 * x / (double)SCWIDTH - 1;
	if ((SCWIDTH - 1) == x)
		camera = 1.0;
	info->ray.raydir_x = info->player.dir_x + info->player.plane_x * camera;
	info->ray.raydir_y = info->player.dir_y + info->player.plane_y * camera;
	info->ray.map_x = (int)info->player.pos_x;
	info->ray.map_y = (int)info->player.pos_y;
	info->ray.deltadist_x = fabs(1 / info->ray.raydir_x);
	info->ray.deltadist_y = fabs(1 / info->ray.raydir_y);
	sidedist_init(&info->ray, &info->player);
}
