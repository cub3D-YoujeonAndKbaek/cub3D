/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cub3D.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kbaek <kbaek@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/07/05 21:39:28 by kbaek			 #+#	#+#			 */
/*   Updated: 2022/07/05 21:41:45 by kbaek			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

//#include "key_macos.h"
#include <math.h>

# include "../libft/include/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define SCWIDTH 640
#define SCHEIGHT 480


# define E 1
# define W 2
# define S 3
# define N 4

typedef struct s_range
{
	int		r;
	int		g;
	int		b;

}			t_range;

typedef struct s_player
{
	double		x;
	double		y;
	int			status;
	double		dirX;
	double 		dirY;
	double		planeX;
	double		planeY;
	double		moveSpeed;
	double		rotSpeed;
}				t_player;

typedef struct s_map
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;

	int			floor;
	int			celling;
	char		**map;

	int			width;
	int			height;
	int			mcount;
	int			start;
	int			ret;
	t_player	player;
}				t_map;

typedef struct s_img
{
	void		*img;
	int			*data;
	int			bpp;
	int			line_size;
	int			endian;
	int			**arr_img;
	int			img_width;
	int			img_height;
	int			buffer[480][640];
}			t_img;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_img		img;
}			t_mlx;

//main.c
int		main(int argc, char **argv);
void	ft_exit(char *ms);

//ft_initialization.c
void	initialization_map(t_map	*map);
void	initialization_img(t_img *img);

//ft_parse.c
void	file_parsing(char *file_name, t_map *map);

//ft_print.c
void	print_struct(t_map *map);

//ft_map_dup.c
void	map_dub(char *file_name, t_map *map);

//ft_key_hook.c
int	key_loop(int keycode, t_mlx *mlx);
int	exit_game(t_mlx *mlx);


#endif
