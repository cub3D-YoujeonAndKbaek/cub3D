/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:48:37 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/19 16:16:00 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	key_hook_w(t_player *p, t_map *map)
{
	double	x_vec;
	double	y_vec;

	x_vec = p->dir_x * p->move_speed;
	y_vec = p->dir_y * p->move_speed;
	if (map->map[(int)(p->pos_y)][(int)(p->pos_x + x_vec * 1.05)] == '0')
		p->pos_x += x_vec;
	if (map->map[(int)(p->pos_y + y_vec * 1.05)][(int)(p->pos_x)] == '0')
		p->pos_y += y_vec;
}

void	key_hook_s(t_player *p, t_map *map)
{
	double	x_vec;
	double	y_vec;

	x_vec = p->dir_x * p->move_speed;
	y_vec = p->dir_y * p->move_speed;
	if (map->map[(int)(p->pos_y)][(int)(p->pos_x - x_vec * 1.05)] == '0')
		p->pos_x -= x_vec;
	if (map->map[(int)(p->pos_y - y_vec * 1.05)][(int)(p->pos_x)] == '0')
		p->pos_y -= y_vec;
}

void	key_hook_a(t_player *p, t_map *map)
{
	double	x_vec;
	double	y_vec;

	x_vec = p->dir_x * p->move_speed;
	y_vec = p->dir_y * p->move_speed;
	if (map->map[(int)(p->pos_y)][(int)(p->pos_x + y_vec * 1.05)] == '0')
		p->pos_x += y_vec;
	if (map->map[(int)(p->pos_y - x_vec * 1.05)][(int)(p->pos_x)] == '0')
		p->pos_y -= x_vec;
}

void	key_hook_d(t_player *p, t_map *map)
{
	double	x_vec;
	double	y_vec;

	x_vec = p->dir_x * p->move_speed;
	y_vec = p->dir_y * p->move_speed;
	if (map->map[(int)(p->pos_y)][(int)(p->pos_x - y_vec * 1.05)] == '0')
		p->pos_x -= y_vec;
	if (map->map[(int)(p->pos_y + x_vec * 1.05)][(int)(p->pos_x)] == '0')
		p->pos_y += x_vec;
}

int	key_hook(t_info *info)
{
	if (info->move.key_w && !info->move.key_s)
		key_hook_w(&info->player, &info->map);
	if (info->move.key_s && !info->move.key_w)
		key_hook_s(&info->player, &info->map);
	if (info->move.key_a && !info->move.key_d)
		key_hook_a(&info->player, &info->map);
	if (info->move.key_d && !info->move.key_a)
		key_hook_d(&info->player, &info->map);
	if (info->move.arr_l && !info->move.arr_r)
		key_hook_l(&info->player);
	if (info->move.arr_r && !info->move.arr_l)
		key_hook_r(&info->player);
	return (1);
}