/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:43:46 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/05 21:43:47 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	print_struct(t_map *map)
{
	int i = 0;
	int j = 0;

	printf("no_path %s\n", map->no_path);
	printf("so_path %s\n", map->so_path);
	printf("we_path %s\n", map->we_path);
	printf("ea_path %s\n", map->ea_path);

	printf("map->floor %x\n", map->floor);
	printf("map->celling %x\n", map->celling);


	printf("map mcount %d\n", map->mcount);
	printf("map start point %d\n", map->start);
	printf("map width %d\n", map->width);
	printf("map height %d\n", map->height);
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			printf("%c", map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("x = %f, y = %f, status = %d\n", map->player.x, map->player.y, map->player.status);
	printf("done\n");

}