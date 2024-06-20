#include "include/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	hook_handler(int keycode, t_param *param)
{
	(void)param;
	if (keycode == ESC)
	{
		printf("exit\n");
		exit(0);
	}
	return (0);
}
