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


int main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc == 2 && file_name_check(argv[1]))
	{
		map_parsing(argv[1], &mlx.map);
		// ft_start_game(&mlx);
		// mlx_hook(mlx.mlx_win, 2, 0, &key_function, &mlx);
		// mlx_hook(mlx.mlx_win, 17, 0, &exit_game, &mlx);
		// mlx_loop_hook(mlx.mlx, &keep_loop, &mlx);
		// mlx_loop(mlx.mlx);
	}
	else
		ft_exit("you should check argvs\n");

}
