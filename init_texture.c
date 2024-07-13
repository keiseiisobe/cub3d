#include "include/cub3d.h"

void	initialize_texture(t_cub3d *info)
{
	t_texture_info	*tmp;

	tmp = &info->map_info.texture_info;
	// North
	tmp->north_img.img = mlx_png_file_to_image(info->mlx_info.mlx, "texture/png/minecraft_bush.png", &tmp->north_tex_width, &tmp->north_tex_height);
	if (!tmp->north_img.img)
		exit(EXIT_FAILURE);
	tmp->north_img.addr = mlx_get_data_addr(tmp->north_img.img, &tmp->north_img.bits_per_pixel, &tmp->north_img.line_length, &tmp->north_img.endian);
	// South
	tmp->south_img.img = mlx_png_file_to_image(info->mlx_info.mlx, "texture/png/minecraft_magma.png", &tmp->south_tex_width, &tmp->south_tex_height);
	if (!tmp->south_img.img)
		exit(EXIT_FAILURE);
	tmp->south_img.addr = mlx_get_data_addr(tmp->south_img.img, &tmp->south_img.bits_per_pixel, &tmp->south_img.line_length, &tmp->south_img.endian);
	// West
	tmp->west_img.img = mlx_png_file_to_image(info->mlx_info.mlx, "texture/png/minecraft_sand.png", &tmp->west_tex_width, &tmp->west_tex_height);
	if (!tmp->west_img.img)
		exit(EXIT_FAILURE);
	tmp->west_img.addr = mlx_get_data_addr(tmp->west_img.img, &tmp->west_img.bits_per_pixel, &tmp->west_img.line_length, &tmp->west_img.endian);
	// East
	tmp->east_img.img = mlx_png_file_to_image(info->mlx_info.mlx, "texture/png/minecraft_wood.png", &tmp->east_tex_width, &tmp->east_tex_height);
	if (!tmp->east_img.img)
		exit(EXIT_FAILURE);
	tmp->east_img.addr = mlx_get_data_addr(tmp->east_img.img, &tmp->east_img.bits_per_pixel, &tmp->east_img.line_length, &tmp->east_img.endian);
}
