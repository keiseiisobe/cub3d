#include "cub3d.h"

size_t	get_input_height(char *filename)
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

char	**get_input(char *filename, size_t height)
{
	int		fd;
	char	*line;
	char	**input;
	size_t	i;

	fd = open(filename, O_RDONLY);
	handle_error(fd < 0);
	input = xmalloc((height + 1) * sizeof(char *));
	i = 0;
	while (i < height)
	{
		line = get_next_line(fd);
		input[i++] = ft_strdup(line);
		free(line);
	}
	input[i] = NULL;
	close(fd);
	return (input);
}

bool	is_png(char *fn)
{
	return (ft_strncmp(fn + ft_strlen(fn) - 4, ".png", 4) == 0);
}

void	set_walls_info(char *fn, t_texture_info *tex_info, char d)
{
	fn[ft_strlen(fn) - 1] = '\0';
	if (d == 'N')
		tex_info->north_texture_filename_ = ft_strdup(fn);
	else if (d == 'S')
		tex_info->south_texture_filename_ = ft_strdup(fn);
	else if (d == 'W')
		tex_info->west_texture_filename_ = ft_strdup(fn);
	else if (d == 'E')
		tex_info->east_texture_filename_ = ft_strdup(fn);
	if (d == 'N')
		tex_info->north_is_png = is_png(fn);
	else if (d == 'S')
		tex_info->south_is_png = is_png(fn);
	else if (d == 'W')
		tex_info->west_is_png = is_png(fn);
	else if (d == 'E')
		tex_info->east_is_png = is_png(fn);
}

void	get_non_map_info(t_map_info *map_info)
{
	size_t	i;
	size_t	k;
	size_t	info_count;
	char	**splited_line;
	char	**rgb_splited_line;

	i = -1;
	info_count = 0;
	while (info_count < 6)
	{
		i++;
		if (map_info->input_[i][0] == '\n')
			continue ;
		splited_line = ft_split(map_info->input_[i], ' ');
		if (splited_line[0][0] == 'N')
			set_walls_info(splited_line[1], &map_info->texture_info, 'N');
		else if (splited_line[0][0] == 'S')
			set_walls_info(splited_line[1], &map_info->texture_info, 'S');
		else if (splited_line[0][0] == 'W')
			set_walls_info(splited_line[1], &map_info->texture_info, 'W');
		else if (splited_line[0][0] == 'E')
			set_walls_info(splited_line[1], &map_info->texture_info, 'E');
		else if (splited_line[0][0] == 'C')
		{
			rgb_splited_line = ft_split(splited_line[1], ',');
			map_info->ceiling_color[0] = ft_atoi(rgb_splited_line[2]);
			map_info->ceiling_color[1] = ft_atoi(rgb_splited_line[1]);
			map_info->ceiling_color[2] = ft_atoi(rgb_splited_line[0]);
			map_info->ceiling_color[3] = 0;
		}
		else if (splited_line[0][0] == 'F')
		{
			rgb_splited_line = ft_split(splited_line[1], ',');
			map_info->floor_color[0] = ft_atoi(rgb_splited_line[2]);
			map_info->floor_color[1] = ft_atoi(rgb_splited_line[1]);
			map_info->floor_color[2] = ft_atoi(rgb_splited_line[0]);
			map_info->floor_color[3] = 0;
		}
		if (splited_line[0][0] == 'C' || splited_line[0][0] == 'F')
		{
			k = 0;
			while (rgb_splited_line[k])
			{
				free(rgb_splited_line[k]);
				k++;
			}
			free(rgb_splited_line);
		}
		k = 0;
		while (splited_line[k])
		{
			free(splited_line[k]);
			k++;
		}
		free(splited_line);
		info_count++;
	}
	i++;
	while (map_info->input_[i][0] == '\n')
		i++;
	map_info->map_start_index = i;

	if (DEBUG)
	{
		printf("===== non_map info =====\n");
		if (map_info->texture_info.north_is_png)
			printf("NO: PNG %s\n", map_info->texture_info.north_texture_filename_);
		else
			printf("NO: XPM %s\n", map_info->texture_info.north_texture_filename_);
		if (map_info->texture_info.south_is_png)
			printf("SO: PNG %s\n", map_info->texture_info.south_texture_filename_);
		else
			printf("SO: XPM %s\n", map_info->texture_info.south_texture_filename_);
		if (map_info->texture_info.west_is_png)
			printf("WE: PNG %s\n", map_info->texture_info.west_texture_filename_);
		else
			printf("WE: XPM %s\n", map_info->texture_info.west_texture_filename_);
		if (map_info->texture_info.east_is_png)
			printf("EA: PNG %s\n", map_info->texture_info.east_texture_filename_);
		else
			printf("EA: XPM %s\n", map_info->texture_info.east_texture_filename_);
		printf("C: %d, %d, %d\n", map_info->ceiling_color[2], map_info->ceiling_color[1], map_info->ceiling_color[0]);
		printf("F: %d, %d, %d\n", map_info->floor_color[2], map_info->floor_color[1], map_info->floor_color[0]);
		printf("========================\n");
	}
	return ;
}

//open close するのは少なくしたい。
//その他、情報をうまく保持できるよう、データ構造自体から変えたい。
//
//validなmapしか入ってこない前提
void	get_map_info(t_map_info *map_info, char *filename)
{
	map_info->input_height = get_input_height(filename);
	map_info->input_ = get_input(filename, map_info->input_height);

	get_non_map_info(map_info);
	map_info->map_height = map_info->input_height - map_info->map_start_index;
	map_info->map = &map_info->input_[map_info->map_start_index];

	if (DEBUG)
	{
		printf("=====map_info=====\n");
		printf("input_height: %zu\n", map_info->input_height);
		printf("map_start_index: %zu\n", map_info->map_start_index);
		printf("map_height: %zu\n", map_info->map_height);
		int i = 0;
		while (map_info->map[i])
		{
			printf("%s", map_info->map[i]);
			i++;
		}
		printf("\n==================\n");
	}
	return ;
}
