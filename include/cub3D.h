
#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

# include "../libft/include/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"

#define TILE_SIZE 30
#define MINI_SCALE 0.25
#define MAP_NUM_COLS 30
#define MAP_NUM_ROWS 30

#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

typedef struct s_map
{
	int			width;
	int			height;
	int			mcount;
	int			ret;
	int			p;
	int			c;
	int			e;
	char		**arr;

}				t_map;


typedef struct    s_mlx
{
    void        *mlx;
    void        *win;
	t_map		map;

}                t_mlx;
 
typedef struct    s_img
{
    void		*img;
    int         *data;
    int         bpp;
    int         line_size;
    int         endian;
}                t_img;


//main.c
int 	main(int argc, char **argv);
void	ft_exit(char *ms);

//ft_parse.c
void	ft_map_parsing(char *file_name, t_map *map);


//ft_initialization.c
void	ft_initialization_map(t_map	*map);

#endif
