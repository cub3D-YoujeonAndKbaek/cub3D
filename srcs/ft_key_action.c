/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:49:51 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/19 16:19:25 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	key_hook_l(t_player *p)
{
	p->dir_y = p->dir_x * sin(-p->rot_speed) + p->dir_y * cos(-p->rot_speed);
	p->dir_x = p->dir_x * cos(-p->rot_speed) - p->dir_y * sin(-p->rot_speed);
	p->plane_y = p->plane_x * sin(-p->rot_speed)
		+ p->plane_y * cos(-p->rot_speed);
	p->plane_x = p->plane_x * cos(-p->rot_speed)
		- p->plane_y * sin(-p->rot_speed);
}

void	key_hook_r(t_player *p)
{
	p->dir_y = p->dir_x * sin(p->rot_speed) + p->dir_y * cos(p->rot_speed);
	p->dir_x = p->dir_x * cos(p->rot_speed) - p->dir_y * sin(p->rot_speed);
	p->plane_y = p->plane_x * sin(p->rot_speed)
		+ p->plane_y * cos(p->rot_speed);
	p->plane_x = p->plane_x * cos(p->rot_speed)
		- p->plane_y * sin(p->rot_speed);
}

void	key_press(int keycode, t_info *info)
{
	if (keycode == K_W)
		info->move.key_w = 1;
	if (keycode == K_S)
		info->move.key_s = 1;
	if (keycode == K_A)
		info->move.key_a = 1;
	if (keycode == K_D)
		info->move.key_d = 1;
	if (keycode == K_AR_R)
		info->move.arr_r = 1;
	if (keycode == K_AR_L)
		info->move.arr_l = 1;
	if (keycode == K_ESC || keycode == 65307)
		exit (0);
}

void	key_release(int keycode, t_info *info)
{
	if (keycode == K_W)
		info->move.key_w = 0;
	if (keycode == K_S)
		info->move.key_s = 0;
	if (keycode == K_A)
		info->move.key_a = 0;
	if (keycode == K_D)
		info->move.key_d = 0;
	if (keycode == K_AR_R)
		info->move.arr_r = 0;
	if (keycode == K_AR_L)
		info->move.arr_l = 0;
}

void	exit_game(t_info *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit (0);
}