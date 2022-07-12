/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:43:49 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/12 21:37:20 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_exit(char *ms)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(ms, 2);
	exit(1);
}

int	file_name_check(char *fn)
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

// 버퍼 초기화
// 텍스쳐 할당 및 초기화
int	image_init(t_img *img)
{
	int	i;
	int j;

	i = 0;
	while (i < SCHEIGHT)
	{
		j = 0;
		while (j < SCWIDTH)
			img->buffer[i][j++] = 0;
		i++;
	}
	img->arr_img = (int **)malloc(5 * sizeof(int *));
	if (!img->arr_img)
		ft_exit("image_init malloc error");
	i = 0;
	while (i < 5)
	{
		img->arr_img[i] = (int *)malloc(sizeof(int) * texWidth * texHeight);
		if (!img->arr_img[i])
			ft_exit("image_init malloc error");
		ft_memset(img->arr_img[i], 0, (sizeof(int) * texWidth * texHeight));
		i++;
	}
	return (0);
}

int	image_load(t_mlx *mlx)
{
	int i;
	char *path;
	int y;
	int x;


	i = 1;
	while (i < 5)
	{
		mlx->img.img_width = 0;
		mlx->img.img_height = 0;
		if (i == E)
			path = mlx->map.ea_path;
		else if (i == W)
			path = mlx->map.we_path;
		else if (i == S)
			path = mlx->map.so_path;
		else
			path = mlx->map.no_path;
		mlx->img.img = mlx_xpm_file_to_image(mlx->mlx, path, &mlx->img.img_width, &mlx->img.img_height);
		if (mlx->img.img_width != texWidth || mlx->img.img_height != texHeight)
			ft_exit("image_load xpm file size error");
		if (mlx->img.img == NULL)
			ft_exit("image_load xpm file get error");
		mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.line_size, &mlx->img.endian);
		y = 0;
		while (y < mlx->img.img_height)
		{
			x = 0;
			while (x < mlx->img.img_width)
			{
				mlx->img.arr_img[i][mlx->img.img_width * y + x] = mlx->img.data[mlx->img.img_width * y + x];
				x++;
			}
			y++;
		}
		mlx_destroy_image(mlx->mlx, mlx->img.img);
		i++;
	}
}

int	set_player(t_player *pl)
{


	pl->dirX = 0;
	pl->dirY = 0;
	if (pl->status == N)
	{
		pl->dirY = -1;
		pl->planeX = 0.66;
	}
	else if (pl->status == S)
	{
		pl->dirY = 1;
		pl->planeX = -0.66;	
	}
	else if (pl->status == W)
	{
		pl->dirX = -1;
		pl->planeY = -0.66;
	}
	else
	{
		pl->dirX = 1;
		pl->planeY = 0.66;
	}
	pl->moveSpeed = 0.05;
	pl->rotSpeed = 0.05;
}

int	start_game(t_mlx *mlx)
{
	image_init(&mlx->img);
	image_load(mlx);
	set_player(&mlx->map.player);
}

void	drow_floor(t_mlx *info)
{
	for(int y = 0; y < SCHEIGHT; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = info->map.player.dirX - info->map.player.planeX;
		float rayDirY0 = info->map.player.dirY - info->map.player.planeY;
		float rayDirX1 = info->map.player.dirX + info->map.player.planeX;
		float rayDirY1 = info->map.player.dirY + info->map.player.planeY;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - SCHEIGHT / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * SCHEIGHT;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCWIDTH;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCWIDTH;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = info->map.player.x + rowDistance * rayDirX0;
		float floorY = info->map.player.y + rowDistance * rayDirY0;

		for(int x = 0; x < SCWIDTH; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int floorTexture = 3;
			int ceilingTexture = 6;

			int color;

			// floor
			color = 255*65536+0*256+0;
			// color = info->texture[floorTexture][texWidth * ty + tx];
			//color = (color >> 1) & 8355711; // make a bit darker

			info->img.buffer[y][x] = color;

			color = 128*65536+128*256+128;
			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			// color = info->texture[ceilingTexture][texWidth * ty + tx];
			//color = (color >> 1) & 8355711; // make a bit darker

			info->img.buffer[SCHEIGHT - y - 1][x] = color;
		}
	}
}

void	calc(t_mlx *info)
{
	int	x;

	drow_floor(info);
	x = 0;
	while (x < SCWIDTH)
	{
		double cameraX = 2 * x / (double)SCWIDTH - 1;

		double rayDirX = info->map.player.dirX + info->map.player.planeX * cameraX;
		double rayDirY = info->map.player.dirY + info->map.player.planeY * cameraX;
		
		int mapX = (int)info->map.player.x;
		int mapY = (int)info->map.player.y;
		// info->map.player.x = 1.5;
		// info->map.player.y = 1.2;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->map.player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->map.player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->map.player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->map.player.y) * deltaDistY;
		}


		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			printf("map x = %d player x = %f\n", mapX, info->map.player.x);
			printf("map y = %d player y = %f\n", mapY, info->map.player.y);
			if (info->map.map[mapY][mapX] == '1')
				hit = 1;
		}
		// printf("map x = %d player x = %f\n", mapX, info->map.player.x);
		// printf("map y = %d player y = %f\n", mapY, info->map.player.y);
		// if (side == 0)
		// 	perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		// else
			// perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		if (side == 0)
			printf("mapX : %d, info->map.player.x : %f, stepX : %d rayDirX : %f perpWallDist : %f \n", mapX, info->map.player.x, stepX, rayDirX, perpWallDist);
		
		//Calculate height of line to draw on screen
		int lineHeight = (int)(SCHEIGHT / perpWallDist);
		printf("lineHeight : %d\n", lineHeight);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCHEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCHEIGHT / 2;
		if(drawEnd >= SCHEIGHT)
			drawEnd = SCHEIGHT - 1;

		// texturing calculations
		int texNum = info->map.map[mapY][mapX];

		// calculate value of wallX
		double wallX;
		if (side == 0)
			wallX = info->map.player.y + perpWallDist * rayDirY;
		else
			wallX = info->map.player.x + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - SCHEIGHT / 2 + lineHeight / 2) * step;
		// printf("y = %d, end = %d\n", drawStart, drawEnd);
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color;
				color = info->img.arr_img[W][texHeight * texY + texX];
			// printf("color = %d", color);
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			info->img.buffer[y][x] = color;
		}
		x++;
	}
}

void	draw(t_mlx *info)
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

int	main_loop(t_mlx *mlx)
{
	calc(mlx);
	draw(mlx);
	return (0);
}


int	main(int argc, char **argv)
{
	t_mlx	mlx;
	// 저장된 맵 변수 불러와서 맵 만들고 렌더링 확인
	// 키 기능 부여
	// 코드 작성
	if (argc == 2 && file_name_check(argv[1]))
	{
		file_parsing(argv[1], &mlx.map);
		mlx.mlx = mlx_init();
		if (!mlx.mlx)
			ft_exit("mlx_init() fail\n");
		mlx.win = mlx_new_window(mlx.mlx, SCWIDTH, SCHEIGHT, "cub3D");	
		if (!mlx.win)
			ft_exit("init_window fail\n");
		start_game(&mlx);
		mlx.img.img = mlx_new_image(mlx.mlx, SCWIDTH, SCHEIGHT);
		mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, &mlx.img.line_size, &mlx.img.endian);
		// mlx_hook(mlx.mlx_win, 2, 0, &key_function, &mlx);
		// mlx_hook(mlx.mlx_win, 17, 0, &exit_game, &mlx);
		// mlx.map.player.x = 1.5;
		// mlx.map.player.y = 1.5;
		// info.posX = 22.0;
		// info.posY = 11.5;
		print_struct(&mlx.map);
		mlx_loop_hook(mlx.mlx, &main_loop, &mlx);
		mlx_loop(mlx.mlx);
	}
	else
		ft_exit("you should check argvs\n");
	// system("leaks cu3D > leak.txt");
}
