/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 02:18:46 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 02:55:04 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	xmlx_file_to_image_ns(t_cub3d *info, t_texture_info *t, char ns)
{
	if (ns == 'N')
	{
		if (t->north_is_png == true)
			t->north_img.img = mlx_png_file_to_image(info->mlx_info.mlx,
					t->north_tex_filename_, &t->north_tex_w, &t->north_tex_h);
		else
			t->north_img.img = mlx_xpm_file_to_image(info->mlx_info.mlx,
					t->north_tex_filename_, &t->north_tex_w, &t->north_tex_h);
		if (!t->north_img.img)
			exit(EXIT_FAILURE);
	}
	else if (ns == 'S')
	{
		if (t->south_is_png == true)
			t->south_img.img = mlx_png_file_to_image(info->mlx_info.mlx,
					t->south_tex_filename_, &t->south_tex_w, &t->south_tex_h);
		else
			t->south_img.img = mlx_xpm_file_to_image(info->mlx_info.mlx,
					t->south_tex_filename_, &t->south_tex_w, &t->south_tex_h);
		if (!t->south_img.img)
			exit(EXIT_FAILURE);
	}
}

void	xmlx_file_to_image_sw(t_cub3d *info, t_texture_info *t, char sw)
{
	if (sw == 'W')
	{
		if (t->west_is_png == true)
			t->west_img.img = mlx_png_file_to_image(info->mlx_info.mlx,
					t->west_tex_filename_, &t->west_tex_w, &t->west_tex_h);
		else
			t->west_img.img = mlx_xpm_file_to_image(info->mlx_info.mlx,
					t->west_tex_filename_, &t->west_tex_w, &t->west_tex_h);
		if (!t->west_img.img)
			exit(EXIT_FAILURE);
	}
	else if (sw == 'E')
	{
		if (t->east_is_png == true)
			t->east_img.img = mlx_png_file_to_image(info->mlx_info.mlx,
					t->east_tex_filename_, &t->east_tex_w, &t->east_tex_h);
		else
			t->east_img.img = mlx_xpm_file_to_image(info->mlx_info.mlx,
					t->east_tex_filename_, &t->east_tex_w, &t->east_tex_h);
		if (!t->east_img.img)
			exit(EXIT_FAILURE);
	}
}

void	initialize_texture(t_cub3d *info)
{
	t_texture_info	*tmp;

	tmp = &info->map_info.texture_info;
	xmlx_file_to_image_ns(info, tmp, 'N');
	tmp->north_img.addr = mlx_get_data_addr(tmp->north_img.img,
			&tmp->north_img.bits_per_pixel,
			&tmp->north_img.line_length, &tmp->north_img.endian);
	xmlx_file_to_image_ns(info, tmp, 'S');
	tmp->south_img.addr = mlx_get_data_addr(tmp->south_img.img,
			&tmp->south_img.bits_per_pixel,
			&tmp->south_img.line_length, &tmp->south_img.endian);
	xmlx_file_to_image_sw(info, tmp, 'W');
	if (!tmp->west_img.img)
		exit(EXIT_FAILURE);
	tmp->west_img.addr = mlx_get_data_addr(tmp->west_img.img,
			&tmp->west_img.bits_per_pixel,
			&tmp->west_img.line_length, &tmp->west_img.endian);
	xmlx_file_to_image_sw(info, tmp, 'E');
	if (!tmp->east_img.img)
		exit(EXIT_FAILURE);
	tmp->east_img.addr = mlx_get_data_addr(tmp->east_img.img,
			&tmp->east_img.bits_per_pixel,
			&tmp->east_img.line_length, &tmp->east_img.endian);
}
