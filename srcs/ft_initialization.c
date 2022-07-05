
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