/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 02:19:44 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 13:36:12 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_walls_info(char *fn, t_texture_info *ti, char d)
{
	fn[ft_strlen(fn) - 1] = '\0';
	if (d == 'N')
		ti->north_tex_filename_ = ft_strdup(fn);
	else if (d == 'S')
		ti->south_tex_filename_ = ft_strdup(fn);
	else if (d == 'W')
		ti->west_tex_filename_ = ft_strdup(fn);
	else if (d == 'E')
		ti->east_tex_filename_ = ft_strdup(fn);
	if (d == 'N')
		ti->north_is_png = (ft_strncmp(fn + ft_strlen(fn) - 4, ".png", 4) == 0);
	else if (d == 'S')
		ti->south_is_png = (ft_strncmp(fn + ft_strlen(fn) - 4, ".png", 4) == 0);
	else if (d == 'W')
		ti->west_is_png = (ft_strncmp(fn + ft_strlen(fn) - 4, ".png", 4) == 0);
	else if (d == 'E')
		ti->east_is_png = (ft_strncmp(fn + ft_strlen(fn) - 4, ".png", 4) == 0);
}

void	set_rgb(t_map_info *map_info, char **splited_line)
{
	char	**rgb_splited_line;

	rgb_splited_line = NULL;
	if (splited_line[0][0] == 'C')
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
	free_2d_char(rgb_splited_line);
}

void	get_non_map_info(t_map_info *map_info)
{
	size_t	i;
	size_t	info_count;
	char	**splited_line;

	i = -1;
	info_count = 0;
	while (info_count < 6)
	{
		if (map_info->input_[++i][0] == '\n')
			continue ;
		splited_line = ft_split(map_info->input_[i], ' ');
		if (splited_line[0][0] == 'N' || splited_line[0][0] == 'S'
			|| splited_line[0][0] == 'W' || splited_line[0][0] == 'E')
			set_walls_info(splited_line[1], &map_info->texture_info,
				splited_line[0][0]);
		else if (splited_line[0][0] == 'C' || splited_line[0][0] == 'F')
			set_rgb(map_info, splited_line);
		free_2d_char(splited_line);
		info_count++;
	}
	i++;
	while (map_info->input_[i][0] == '\n')
		i++;
	map_info->map_start_index = i;
	return ;
}

void	get_map_info(t_map_info *map_info, char *filename)
{
	map_info->input_height = get_input_height(filename);
	map_info->input_ = get_input(filename, map_info->input_height);
	get_non_map_info(map_info);
	print_non_map_info(map_info);
	map_info->map_height = map_info->input_height - map_info->map_start_index;
	map_info->map = &map_info->input_[map_info->map_start_index];
	print_map_info(map_info);
	return ;
}
