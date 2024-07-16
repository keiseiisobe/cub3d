/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:04:16 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 13:48:29 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_non_map_info(t_map_info *map_info)
{
	if (DEBUG)
	{
		printf("===== non_map info =====\n");
		if (map_info->texture_info.north_is_png)
			printf("NO: PNG %s\n", map_info->texture_info.north_tex_filename_);
		else
			printf("NO: XPM %s\n", map_info->texture_info.north_tex_filename_);
		if (map_info->texture_info.south_is_png)
			printf("SO: PNG %s\n", map_info->texture_info.south_tex_filename_);
		else
			printf("SO: XPM %s\n", map_info->texture_info.south_tex_filename_);
		if (map_info->texture_info.west_is_png)
			printf("WE: PNG %s\n", map_info->texture_info.west_tex_filename_);
		else
			printf("WE: XPM %s\n", map_info->texture_info.west_tex_filename_);
		if (map_info->texture_info.east_is_png)
			printf("EA: PNG %s\n", map_info->texture_info.east_tex_filename_);
		else
			printf("EA: XPM %s\n", map_info->texture_info.east_tex_filename_);
		printf("C: %d, %d, %d\n", map_info->ceiling_color[2],
			map_info->ceiling_color[1], map_info->ceiling_color[0]);
		printf("F: %d, %d, %d\n", map_info->floor_color[2],
			map_info->floor_color[1], map_info->floor_color[0]);
		printf("========================\n");
	}
}

void	print_map_info(t_map_info *map_info)
{
	int	i;

	i = 0;
	if (DEBUG)
	{
		printf("=====map_info=====\n");
		printf("input_height: %zu\n", map_info->input_height);
		printf("map_start_index: %zu\n", map_info->map_start_index);
		printf("map_height: %zu\n", map_info->map_height);
		while (map_info->map[i])
		{
			printf("%s", map_info->map[i]);
			i++;
		}
		printf("\n==================\n");
	}
}
