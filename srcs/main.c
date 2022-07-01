#include "../include/cub3D.h"

void	ft_exit(char *ms)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(ms, 2);
	exit(1);
}

int	ft_file_name_check(char *fn)
{
	int		len;
	char	*ber;
	int		i;

	len = ft_strlen(fn);
	ber = ".cub";
	if (len > 4)
	{
		i = 4;
		while (i >= 0)
		{
			if (!(fn[len] == ber[i]))
				return (0);
			len--;
			i--;
		}
		return (1);
	}
	else
		return (0);
}


int main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc == 2 && ft_file_name_check(argv[1]))
	{
		ft_map_parsing(argv[1], &mlx.map);
		// ft_start_game(&mlx);
		// mlx_hook(mlx.mlx_win, 2, 0, &key_function, &mlx);
		// mlx_hook(mlx.mlx_win, 17, 0, &exit_game, &mlx);
		// mlx_loop_hook(mlx.mlx, &keep_loop, &mlx);
		// mlx_loop(mlx.mlx);
	}
	else
		ft_exit("you should check file name\n");

}

/*
const int mini_map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


void fill_squares(t_img *map, int x, int y, int color)
{
	int i;
	int j;

	j = 0;
	while (j < (int)(MINI_SCALE * TILE_SIZE))
	{
		i = 0;
		while (i < (int)(MINI_SCALE * TILE_SIZE))
		{
			map->data[(int)(MINI_SCALE * WINDOW_WIDTH) * (y + j) + (x + i)] = color;
			i++;
		}
		j++;
	}
}


void	render_map(t_mlx *mlx, t_img *map)
{
	map->data = (int *)mlx_get_data_addr(map->img, &(map->bpp), &(map->line_size), &(map->endian));
	int col;
	int row;

	row = 0;
	while (row < MAP_NUM_ROWS)
	{
		col = 0;
		while (col < MAP_NUM_COLS)
		{
			if (mini_map[row][col] == 1)
				fill_squares(map, (int)(MINI_SCALE * TILE_SIZE * col), (int)(MINI_SCALE * TILE_SIZE * row), 0x000000);
			else
				fill_squares(map, (int)(MINI_SCALE * TILE_SIZE * col), (int)(MINI_SCALE * TILE_SIZE * row), 0xffffff);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, map->img, (int)(WINDOW_WIDTH * (1 - MINI_SCALE)), (int)(WINDOW_HEIGHT * (1 - MINI_SCALE)));
}

int        main2(void)
{
    t_mlx    mlx;
    t_img    map;
 
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "title");
    map.img = mlx_new_image(mlx.mlx, (int)(MINI_SCALE * WINDOW_WIDTH), (int)(MINI_SCALE * WINDOW_HEIGHT));
	render_map(&mlx, &map);
    mlx_loop(mlx.mlx);
    return (0);
}

*/