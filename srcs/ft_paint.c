#include "../include/cub3D.h"

void	paint_floor(t_info *info)
{
	
}

void	paint_img(t_info *info)
{
	for (int y = 0; y < SCHEIGHT; y++)
	{
		for (int x = 0; x < SCWIDTH; x++)
		{
			info->img.data[y * SCWIDTH + x] = info->img.buffer[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}