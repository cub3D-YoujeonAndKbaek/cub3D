/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:43:49 by kbaek             #+#    #+#             */
/*   Updated: 2022/07/20 15:36:16 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	main_loop(t_info *info)
{
	paint_floor(info);
	raycasting(info);
	paint_img(info);
	key_hook(info);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc == 2 && file_name_check(argv[1]))
	{
		file_parsing(argv[1], &info);
		start_game(&info);
		info.img.img = mlx_new_image(info.mlx, SCWIDTH, SCHEIGHT);
		info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp,
				&info.img.line_size, &info.img.endian);
		mlx_hook(info.win, 17, 0, &exit_game, &info);
		mlx_hook(info.win, 2, 0, &key_press, &info);
		mlx_hook(info.win, 3, 0, &key_release, &info);
		mlx_loop_hook(info.mlx, &main_loop, &info);
		mlx_loop(info.mlx);
	}
	else
		ft_exit("you should check argvs\n");
}
