/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 02:20:20 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 15:06:03 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fc(t_mlx_info *mlx_info, int color, size_t begin_y, size_t end_y)
{
	size_t	begin_x;
	size_t	end_x;

	end_x = mlx_info->win_width;
	while (begin_y < end_y)
	{
		begin_x = 0;
		while (begin_x < end_x)
		{
			my_mlx_pixel_put(&mlx_info->img_data, begin_x, begin_y, color);
			begin_x++;
		}
		begin_y++;
	}
}

void	get_raycast_vector(t_player_info *player_info)
{
	if (player_info->ray_x < 0)
	{
		player_info->step_x = -1;
		player_info->side_x = (player_info->pos_x - player_info->map_x)
			* player_info->delta_x;
	}
	else if (player_info->ray_x >= 0)
	{
		player_info->step_x = 1;
		player_info->side_x = ((player_info->map_x + 1) - player_info->pos_x)
			* player_info->delta_x;
	}
	if (player_info->ray_y < 0)
	{
		player_info->step_y = -1;
		player_info->side_y = (player_info->pos_y - player_info->map_y)
			* player_info->delta_y;
	}
	else if (player_info->ray_y >= 0)
	{
		player_info->step_y = 1;
		player_info->side_y = ((player_info->map_y + 1) - player_info->pos_y)
			* player_info->delta_y;
	}
}

void	ready_to_raycast(t_mlx_info *mlx_info,
		t_player_info *player_info, size_t i)
{
	player_info->camera_x = 2 / (double)mlx_info->win_width * i - 1;
	player_info->ray_x
		= player_info->dir_x + player_info->plane_x * player_info->camera_x;
	player_info->ray_y
		= player_info->dir_y + player_info->plane_y * player_info->camera_x;
	player_info->map_x = (size_t)player_info->pos_x;
	player_info->map_y = (size_t)player_info->pos_y;
	if (player_info->ray_x == 0)
		player_info->delta_x = 1e30;
	else
		player_info->delta_x = fabs(1 / player_info->ray_x);
	if (player_info->ray_y == 0)
		player_info->delta_y = 1e30;
	else
		player_info->delta_y = fabs(1 / player_info->ray_y);
	get_raycast_vector(player_info);
}

void	raycast_until_hit_wall(t_player_info *player_info, t_map_info *map_info)
{
	while (1)
	{
		if (player_info->side_x < player_info->side_y)
		{
			player_info->side_x += player_info->delta_x;
			player_info->map_x += player_info->step_x;
			if (player_info->step_x == -1)
				player_info->wall_side = WEST;
			else
				player_info->wall_side = EAST;
		}
		else if (player_info->side_x >= player_info->side_y)
		{
			player_info->side_y += player_info->delta_y;
			player_info->map_y += player_info->step_y;
			if (player_info->step_y == -1)
				player_info->wall_side = NORTH;
			else
				player_info->wall_side = SOUTH;
		}
		if (map_info->map[player_info->map_y][player_info->map_x] == '1')
			break ;
	}
}

void	draw_loop(t_cub3d *info)
{
	size_t	i;
	size_t	wall_height;

	i = 0;
	draw_fc(&info->mlx_info, *(int *)info->map_info.floor_color,
		info->mlx_info.win_height / 2, info->mlx_info.win_height);
	draw_fc(&info->mlx_info, *(int *)info->map_info.ceiling_color,
		0, info->mlx_info.win_height / 2);
	while (i < info->mlx_info.win_width)
	{
		ready_to_raycast(&info->mlx_info, &info->player_info, i);
		raycast_until_hit_wall(&info->player_info, &info->map_info);
		wall_height = get_wall_height(&info->player_info);
		draw_vertical_line(info, wall_height, i);
		i++;
	}
}
