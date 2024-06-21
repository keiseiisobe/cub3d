#include "include/cub3d.h"

int	get_wall_color(int wall_side)
{
	if (wall_side == NORTH)
		return (0x00FF0000);
	else if (wall_side == SOUTH)
		return (0x0000FF00);
	else if (wall_side == WEST)
		return (0x000000FF);
	else // wall_side == EAST
		return (0x0000FFFF);
}

void	draw_vertical_line(t_data *data, size_t win_height, size_t wall_height, size_t i, int color)
{
	size_t	begin_x;
	size_t	begin_y;
	size_t	current_height;

	begin_x = i;
	begin_y = (win_height / 2) - (wall_height / 2);
	current_height = 0;
	while (current_height < wall_height)
	{
		my_mlx_pixel_put(data, begin_x, begin_y++, color);
		current_height++;
	}
}

void	draw_loop(t_mlx_info *mlx_info, t_map_info *map_info, t_player_info *player_info)
{
	double	i;
	int		hit;
	size_t	wall_height;
	int		color;

	i = 0;
	while(i < mlx_info->win_width)
	{
		player_info->camera_x = 2 / (double)mlx_info->win_width * i - 1;
		player_info->ray_x = player_info->dir_x + player_info->plane_x * player_info->camera_x; // it depends on the player direction.
		player_info->ray_y = player_info->dir_y + player_info->plane_y * player_info->camera_x; // N or S or W or E. in this case, N.
		player_info->map_x = (int)player_info->pos_x;
		player_info->map_y = (int)player_info->pos_y;
		player_info->delta_x = (player_info->ray_x == 0) ? 1e30 : fabs(1 / player_info->ray_x);
		player_info->delta_y = (player_info->ray_y == 0) ? 1e30 : fabs(1 / player_info->ray_y);
		if (player_info->ray_x < 0)
		{
			player_info->step_x = -1;
			player_info->side_x = (player_info->pos_x - player_info->map_x) * player_info->delta_x;
		}
		else // ray_x >= 0
		{
			player_info->step_x = 1;
			player_info->side_x = ((player_info->map_x + 1) - player_info->pos_x) * player_info->delta_x;
		}
		if (player_info->ray_y < 0)
		{
			player_info->step_y = -1;
			player_info->side_y = (player_info->pos_y - player_info->map_y) * player_info->delta_y;
		}
		else // ray_y >= 0
		{
			player_info->step_y = 1;
			player_info->side_y = ((player_info->map_y + 1) - player_info->pos_y) * player_info->delta_y;
		}
		hit = 0;
		while (hit == 0)
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
			else // side_y < side_x
			{
				player_info->side_y += player_info->delta_y;
				player_info->map_y += player_info->step_y;
				if (player_info->step_y == -1)
					player_info->wall_side = NORTH;
				else
					player_info->wall_side = SOUTH;
			}
			if (map_info->map[player_info->map_y][player_info->map_x] != '0')
				hit = 1;
		}
		if (player_info->wall_side == NORTH || player_info->wall_side == SOUTH)
			player_info->perpendicular_distance_to_wall = player_info->side_y - player_info->delta_y;
		else // player_info->wall_side == WEST || EAST
			player_info->perpendicular_distance_to_wall = player_info->side_x - player_info->delta_x;
		wall_height = (int)(WALL_SIZE_WEIGHT / player_info->perpendicular_distance_to_wall);
		color = get_wall_color(player_info->wall_side);
		draw_vertical_line(&mlx_info->img_data, mlx_info->win_height, wall_height, (size_t)i, color);
		i++;
	}
}
