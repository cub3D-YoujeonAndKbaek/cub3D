
#include "../include/cub3D.h"

void	print_struct(t_map *map)
{
	printf("no_path %s\n", map->no_path);
	printf("so_path %s\n", map->so_path);
	printf("we_path %s\n", map->we_path);
	printf("ea_path %s\n", map->ea_path);

	printf("map->floor %x\n", map->floor);
	printf("map->celling %x\n", map->celling);
}


int ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int		deep_cheak(t_map *map, char *line, char **tmp)
{
	line += 2;
	while (ft_isspace(*line))
		line++;
	int fd;
	fd = open(line, O_RDONLY);
	if (fd == -1)
		ft_exit("texture errer");
	close(fd);
	*tmp = ft_strdup(line);
}

void	direction_check(t_map *map, char *line, char c)
{

	char *tmp;

	if (c == 'N')
	{
		if (deep_cheak(map, line, &tmp))
			map->no_path = tmp;
	}
	else if (c == 'S')
	{
		if (deep_cheak(map, line, &tmp))
			map->so_path = tmp;
	}
	else if (c == 'W')
	{
		if (deep_cheak(map, line, &tmp))
			map->we_path = tmp;
	}
	else if (c == 'E')
	{
		if (deep_cheak(map, line, &tmp))
			map->ea_path = tmp;
	}
}

void	range_number_check(char *line)
{
	int i;

	i = 0;
	if (!ft_isdigit(*line))
		ft_exit("rgb digit error");
	while(*line)
	{
		if (*line == ',')
		{
			i++;
			line++;
			while(ft_isspace(*line))
				line++;
		}
		if (!ft_isdigit(*line))
			ft_exit("rgb error");
		line++;
	}
	if (i != 2)
		ft_exit("range error");
}

int set_rgb(char **line)
{
	int rt;
	int i;

	rt = ft_atoi(*line);
	i = 1;
	while (rt > i)
	{
		(*line)++;
		i *= 10;
	}
	(*line)++;
	while(!ft_strncmp(",", (*line), ft_strlen(*line)) || ft_isspace(**line))
		(*line)++;
	return (rt);
}

void	color_check(t_map *map, char *line, char c)
{
	t_range rgb;

	line += 2;
	while (ft_isspace(*line))
		line++;
	range_number_check(line);
	rgb.r = set_rgb(&line);
	rgb.g = set_rgb(&line);
	rgb.b = set_rgb(&line);
	if (!(rgb.r >= 0 && rgb.r <= 255) || !(rgb.g >= 0 && rgb.g <= 255)
		|| !(rgb.b >= 0 && rgb.b <= 255))
		ft_exit("it is nor 0 ~ 255");
	if (c == 'F')
	{
		map->floor = (rgb.r << 16 | rgb.g << 8 | rgb.b);
	}
	else
	{
		map->celling = (rgb.r << 16 | rgb.g << 8 | rgb.b);
	}
}

// void	map_check(t_map *map, char *line)
// {
	
// }

int	map_check(t_map *map, char *line)
{
	int i;

	i = 0;
	if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3) 
		|| !ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3))
		direction_check(map, line, line[0]);
	else if (!ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2))
		color_check(map, line, line[0]);
	while (ft_isspace(line[i]))
		i++;
	// if (line[i] == '0' || line[i] == '1')
	// 	map_check(map, &line);
	return (1);
}

void map_parsing(char *file_name, t_map *map)
{
	char	*line;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_exit("file open error\n");
	initialization_map(map);
	while (map->ret == 1)
	{
		map->ret = ft_get_next_line(fd, &line);
		if (map->ret == -1)
			ft_exit("error");
		map_check(map, line);
		free(line);
		line = NULL;
	}
	print_struct(map);
	close (fd);
	map->ret = 1;
	//ft_fill_map(line, map, file_name);
	close (fd);
}