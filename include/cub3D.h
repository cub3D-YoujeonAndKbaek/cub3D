
#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

# include "../libft/include/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"


typedef struct s_range
{
	int		r;
	int		g;
	int		b;

}			t_range;


typedef struct s_map
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;

	int		floor;
	int		celling;	

	char		**map;
	
	// int			width;
	// int			height;
	// int			mcount;
	int			ret;
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
void	map_parsing(char *file_name, t_map *map);


//ft_initialization.c
void	initialization_map(t_map	*map);

#endif
