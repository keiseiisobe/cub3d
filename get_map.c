#include "include/cub3d.h"

size_t	get_map_height(char *filename)
{
	int		fd;
	char	*line;
	size_t	height;

	fd = open(filename, O_RDONLY);
	handle_error(fd < 0);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		height++;
	}
	close(fd);
	return (height);
}

size_t	get_map_width(char *filename)
{
	int		fd;
	char	*line;
	size_t	width;

	fd = open(filename, O_RDONLY);
	handle_error(fd < 0);
	width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (width < strlen(line) - 1) // "-1" can remove new line.
			width = strlen(line) - 1; // but, need to handle when there is no new line.
		free(line);
	}
	close(fd);
	return (width);
}

void	get_map_info(t_map_info *map_info, char *filename)
{
	int		fd;
	char	*line;
	size_t	i;

	map_info->map_height = get_map_height(filename);
	map_info->map_width = get_map_width(filename);
	fd = open(filename, O_RDONLY);
	handle_error(fd < 0);
	map_info->map = xmalloc((map_info->map_height + 1) * sizeof(char *));
	i = 0;
	while (i < map_info->map_height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map_info->map[i++] = strdup(line); // have to handle the space in tetris shape map.
		free(line);
	}
	map_info->map[i] = NULL;
	close(fd);
}
