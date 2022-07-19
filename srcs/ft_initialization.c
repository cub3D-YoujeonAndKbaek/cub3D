/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:43:35 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/19 21:38:50 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	initialization_map(t_map	*map)
{
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->floor = -1;
	map->celling = -1;
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->mcount = 0;
	map->start = 0;
	map->ret = 1;
}

void	initialization_img(t_img *img)
{
	img->img = NULL;
	img->data = NULL;
	img->bpp = 0;
	img->line_size = 0;
	img->endian = 0;
	img->arr_img = NULL;
}

void	initialization_move(t_move *move)
{
	move->key_w = 0;
	move->key_a = 0;
	move->key_s = 0;
	move->key_d = 0;
	move->arr_l = 0;
	move->arr_r = 0;
}
