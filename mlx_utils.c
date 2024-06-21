#include "include/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	turn_left(t_player_info *player_info)
{
	if (player_info->dir_x == 0) // North or South
	{
		player_info->dir_x = player_info->dir_y;
		player_info->dir_y = 0;
		player_info->plane_x = 0;
		player_info->plane_y = 0.66;
	}
	else if (player_info->dir_y == 0) // West or East
	{
		player_info->dir_y = player_info->dir_x * -1;
		player_info->dir_x = 0;
		player_info->plane_x = 0.66;
		player_info->plane_y = 0;
	}
}

void	turn_right(t_player_info *player_info)
{
	if (player_info->dir_x == 0) // North or South
	{
		player_info->dir_x = player_info->dir_y * -1;
		player_info->dir_y = 0;
		player_info->plane_x = 0;
		player_info->plane_y = 0.66;
	}
	else if (player_info->dir_y == 0) // West or East
	{
		player_info->dir_y = player_info->dir_x;
		player_info->dir_x = 0;
		player_info->plane_x = 0.66;
		player_info->plane_y = 0;
	}
}

int	hook_handler(int keycode, t_param *param)
{
	t_data	*tmp_img_data;

	printf("keycode: %d\n", keycode);
	if (keycode == ESC)
	{
		printf("exit\n");
		exit(0);
	}
	if (keycode == 13) // forward (W)
		param->player_info->pos_y += -0.1;
	else if (keycode == 1) // backward (S)
		param->player_info->pos_y += 0.1;
	else if (keycode == 0) // left (A)
		param->player_info->pos_x += -0.1;
	else if (keycode == 2) // right (D)
		param->player_info->pos_x += 0.1;
	else if (keycode == 123) // turn left (<-)
		turn_left(param->player_info);
	else if (keycode == 124) // turn right (->)
		turn_right(param->player_info);
	if (keycode == 13 || (keycode >= 0 && keycode <= 2) || keycode == 123 || keycode == 124)
	{
		tmp_img_data = &param->mlx_info->img_data;
		param->mlx_info->img_data.img = mlx_new_image(param->mlx_info->mlx, param->mlx_info->win_width, param->mlx_info->win_height);
		param->mlx_info->img_data.addr = mlx_get_data_addr(param->mlx_info->img_data.img, &param->mlx_info->img_data.bits_per_pixel, &param->mlx_info->img_data.line_length, &param->mlx_info->img_data.endian);
		game(param);
		mlx_destroy_image(param->mlx_info->mlx, tmp_img_data->img);
	}
	return (0);
}
