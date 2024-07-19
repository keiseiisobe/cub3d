/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 02:20:02 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/19 13:10:10 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_next_image(t_mlx_info *mlx_info, t_cub3d *info)
{
	mlx_info->img_data.img
		= mlx_new_image(mlx_info->mlx, mlx_info->win_width,
			mlx_info->win_height);
	mlx_info->img_data.addr
		= mlx_get_data_addr(mlx_info->img_data.img,
			&mlx_info->img_data.bits_per_pixel,
			&mlx_info->img_data.line_length, &mlx_info->img_data.endian);
	game(info);
}

void	move_handler(int keycode, t_cub3d *info)
{
	t_data	*tmp_img_data;

	if (keycode == 13)
		walk_forward(&info->player_info, info->map_info.map);
	else if (keycode == 1)
		walk_backward(&info->player_info, info->map_info.map);
	else if (keycode == 0)
		walk_left(&info->player_info, info->map_info.map);
	else if (keycode == 2)
		walk_right(&info->player_info, info->map_info.map);
	else if (keycode == 123)
		turn_left(&info->player_info);
	else if (keycode == 124)
		turn_right(&info->player_info);
	if (keycode == 13 || (keycode >= 0 && keycode <= 2)
		|| keycode == 123 || keycode == 124)
	{
		tmp_img_data = &info->mlx_info.img_data;
		render_next_image(&info->mlx_info, info);
		mlx_destroy_image(info->mlx_info.mlx, tmp_img_data->img);
	}
}

int	event_handler(int keycode, t_cub3d *info)
{
	if (keycode == ESC)
	{
		printf("exit\n");
		mlx_destroy_window(info->mlx_info.mlx, info->mlx_info.mlx_win);
		free_all(&info->map_info);
		exit(EXIT_SUCCESS);
	}
	move_handler(keycode, info);
	return (0);
}

int	x_bottun_handler(t_cub3d *info)
{
	printf("exit\n");
	mlx_destroy_window(info->mlx_info.mlx, info->mlx_info.mlx_win);
	free_all(&info->map_info);
	exit(EXIT_SUCCESS);
	return (0);
}
