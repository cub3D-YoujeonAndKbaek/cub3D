/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:43:35 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/05 21:44:52 by kbaek            ###   ########.fr       */
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
	map->player.status = 0;
	// map->width = 0;
	// map->p = 0;
	// map->c = 0;
	// map->e = 0;
	// map->arr = 0;
}
