
#include "../include/cub3D.h"



// void	read_file(t_info *cub)
// {
// 	char	*line;
// 	int		type;
// 	int		c;
// 	char	**word;

// 	c = 0;
// 	while (get_next_line(cub->fd, &line) > 0)
// 	{
// 		if (line[0] == '\0')
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		c = ft_cntword(line, ' ');
// 		word = ft_split(line, ' ');
// 		if (!word)
// 			ft_exit("ERROR: Fail to split lines");
// 		type = valid_and_set_element_lines(cub, word, c);
// 		ft_free2d(word);
// 		if (type == MAP)
// 			break ;
// 		free(line);
// 	}
// 	cub->map_lines = ft_lstnew(ft_strdup(line));
// 	free(line);
// }

void	ft_fill_map(char *line, t_map *map, char *fn)
{
	int	i;
	int	fd;

	fd = open(fn, O_RDONLY);
	if (map->p > 1 || map->p == 0 || map->c == 0 || map->e == 0)
		ft_exit("number of characters wrong\n");
	map->arr = malloc(sizeof(char *) * (map->height + 1));
	if (!map->arr)
		ft_exit("malloc error\n");
	i = 0;
	while (map->ret == 1)
	{
		map->ret = ft_get_next_line(fd, &map->arr[i]);
		if (!map->arr[i])
			break ;
		free(line);
		line = NULL;
		i++;
	}
	map->arr[i] = NULL;
	if (map->ret == -1)
	{
		free (map->arr);
		ft_exit("copying map is not work\n");
	}
}

void ft_map_parsing(char *file_name, t_map *map)
{
	char	*line;
	int		fd;
	int		type;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_exit("file open error\n");
	ft_initialization_map(map);
	while (map->ret == 1)
	{
		map->ret = ft_get_next_line(fd, &line);
		if (!line)
		{
			free(line);
			continue;
		}
		ft_map_error_check(map, line);
		free(line);
		line = NULL;
	}
	close (fd);
	map->ret = 1;
	ft_fill_map(line, map, file_name);
	close (fd);
}