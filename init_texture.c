#include "include/cub3d.h"

void	initialize_texture(t_cub3d *info)
{
	void	*mlx;
	t_data	north_img;
	t_data	south_img;
	t_data	west_img;
	t_data	east_img;
	int		width;
	int		height;

	mlx = mlx_init();
	// North
	north_img.img = mlx_png_file_to_image(mlx, "./texture/png/redbrick.png", &width, &height);
	if (!north_img.img)
		exit(EXIT_FAILURE);
	north_img.addr = mlx_get_data_addr(north_img.img, &north_img.bits_per_pixel, &north_img.line_length, &north_img.endian);
	info->map_info.north_texture_ = north_img.addr;

	printf("width: %d\n", width);
	printf("height: %d\n", height);
	printf("bpp: %d\n", north_img.bits_per_pixel);
	printf("line_length: %d\n", north_img.line_length);
/*
	int	dst;
	int	y = 0;
	while (y < 4)
	{
		int	x = 0;
		while (x < 64)
		{
			dst = *(unsigned int *)(info->map_info.north_texture_ + (y * north_img.line_length) + (x++ * 4));
			printf("%x ", dst);
		}
		printf("\n");
		y++;
	}
*/
	// South
	south_img.img = mlx_png_file_to_image(mlx, "texture/png/bluestone.png", &width, &height);
	south_img.addr = mlx_get_data_addr(south_img.img, &south_img.bits_per_pixel, &south_img.line_length, &south_img.endian);
	info->map_info.south_texture_ = south_img.addr;
//	mlx_destroy_image(mlx, img.img);
	// West
	west_img.img = mlx_png_file_to_image(mlx, "texture/png/colorstone.png", &width, &height);
	west_img.addr = mlx_get_data_addr(west_img.img, &west_img.bits_per_pixel, &west_img.line_length, &west_img.endian);
	info->map_info.west_texture_ = west_img.addr;
//	mlx_destroy_image(mlx, img.img);
	// East
	east_img.img = mlx_png_file_to_image(mlx, "texture/png/purplestone.png", &width, &height);
	east_img.addr = mlx_get_data_addr(east_img.img, &east_img.bits_per_pixel, &east_img.line_length, &east_img.endian);
	info->map_info.east_texture_ = east_img.addr;
	// tex_width and tex_height
	info->map_info.tex_width = width;
	info->map_info.tex_height = height;
//	mlx_destroy_image(mlx, img.img);
}
