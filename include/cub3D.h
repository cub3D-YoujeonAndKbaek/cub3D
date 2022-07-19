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
# include <math.h>

# include "../libft/include/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17
# define texWidth 64
# define texHeight 64
# define mapWidth 24
# define mapHeight 24
# define SCWIDTH 720
# define SCHEIGHT 480

# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2
# define K_AR_L 123
# define K_AR_R 124
# define K_ESC 53
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
	int			status;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double 		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct s_map
{
	char		**map;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor;
	int			celling;
	int			width;
	int			height;
	int			mcount;
	int			start;
	int			ret;
}				t_map;

typedef struct s_img
{
	void		*img;
	int			*data;
	int			bpp;
	int			line_size;
	int			endian;
	int			w;
	int			h;
	int			buffer[SCHEIGHT][SCWIDTH];
	int			**arr_img;
}			t_img;

typedef struct s_move
{
	int	key_w;
	int key_s;
	int	key_a;
	int	key_d;
	int	arr_l;
	int	arr_r;
}			t_move;

typedef struct s_info
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_img		img;
	t_player	player;
	t_move		move;
}			t_info;



//main.c
int		main(int argc, char **argv);
void	ft_exit(char *ms);

//ft_initialization.c
void	initialization_map(t_map	*map);
void	initialization_move(t_move *move);
void	initialization_img(t_img *img);

//ft_parse.c
void	file_parsing(char *file_name, t_info *info);

//ft_parse_util.c
void	direction_check(t_map *map, char *line, char c);
void	color_check(t_map *map, char *line, char c);

//ft_print.c
void	print_struct(t_map *map);

//ft_map_dup.c
void	map_dub(char *file_name, t_info *info);

//ft_start_game.c
void	start_game(t_info *info);

//ft_paint.c
void	paint_img(t_info *info);
void	paint_floor(t_info *info);

//ft_key_hook.c
int		key_hook(t_info *info);

//ft_key_action.c
void		key_hook_l(t_player *p);
void		key_hook_r(t_player *p);
void		key_release(int keycode, t_info *info);
void		key_press(int keycode, t_info *info);
void	exit_game(t_info *mlx);

#endif
