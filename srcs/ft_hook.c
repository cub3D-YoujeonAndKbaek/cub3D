#include "../include/cub3D.h"


// int	key_hook(int keycode, t_mlx *mlx)
// {
// 	if (keycode == 53 || keycode == 65307)
// 		exit (0);
// 	else if (keycode == W || keycode == S)
// 		key_hook_ws(keycode, mlx);
// 	else if (keycode == E || keycode == N)
// 		key_hook_en(keycode, mlx);
// 	else if (keycode == LEFT || keycode == RIGHT)
// 		key_hook_lr(keycode, mlx);
// 	return (1);
// }


// int	key_loop(int keycode, t_mlx *mlx)
// {
// 	if (keycode == 53 || keycode == 65307)
// 		exit (0);
// 	if (keycode == 13 || keycode == 126)
// 		mlx->key.w = 1;
// 	else if (keycode == 0 || keycode == 123)
// 		mlx->key.a = 1;
// 	else if (keycode == 1 || keycode == 125)
// 		mlx->key.s = 1;
// 	else if (keycode == 2 || keycode == 124)
// 		mlx->key.d = 1;
// 	return (0);
// }

int	exit_game(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit (0);
}