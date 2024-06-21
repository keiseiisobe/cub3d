#include "include/cub3d.h"

void	game(t_param *param)
{
	draw_loop(param->mlx_info, param->map_info, param->player_info);
	mlx_put_image_to_window(param->mlx_info->mlx, param->mlx_info->mlx_win, param->mlx_info->img_data.img, 0, 0);
}
