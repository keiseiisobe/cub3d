/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 02:12:38 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 13:39:53 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	handle_error(!ptr && errno == ENOMEM);
	return (ptr);
}

void	destroy_all_image(t_cub3d *info)
{
	mlx_destroy_image(info->mlx_info.mlx, info->mlx_info.img_data.img);
	mlx_destroy_image(info->mlx_info.mlx,
		info->map_info.texture_info.north_img.img);
	mlx_destroy_image(info->mlx_info.mlx,
		info->map_info.texture_info.south_img.img);
	mlx_destroy_image(info->mlx_info.mlx,
		info->map_info.texture_info.west_img.img);
	mlx_destroy_image(info->mlx_info.mlx,
		info->map_info.texture_info.east_img.img);
}

void	free_all(t_map_info *map_info)
{
	free_2d_char(map_info->input_);
	free(map_info->texture_info.north_tex_filename_);
	free(map_info->texture_info.south_tex_filename_);
	free(map_info->texture_info.west_tex_filename_);
	free(map_info->texture_info.east_tex_filename_);
}
