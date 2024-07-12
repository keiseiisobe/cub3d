#include "include/cub3d.h"

void	initialize_texture(t_cub3d *info)
{
	void	*mlx;
	t_data	img;
	size_t	width;
	size_t	height;

	mlx = mlx_init();
	// North
	img.img = mlx_png_file_to_image(mlx, "pics/redbrick.png", &width, &height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	info->map_info.north_texture_ = strdup(img.addr);
	mlx_destroy_image(mlx, img.img);
	// South
	img.img = mlx_png_file_to_image(mlx, "pics/bluestone.png", &width, &height);
	info->map_info.south_texture_ = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_destroy_image(mlx, img.img);
	// West
	img.img = mlx_png_file_to_image(mlx, "pics/greystone.png", &width, &height);
	info->map_info.west_texture_ = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_destroy_image(mlx, img.img);
	// East
	img.img = mlx_png_file_to_image(mlx, "pics/wood.png", &width, &height);
	info->map_info.east_texture_ = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
i	// tex_width and tex_height
	info->map_info.tex_width = width;
	info->map_info.tex_height = height;
	mlx_destroy_image(mlx, img.img);
}
