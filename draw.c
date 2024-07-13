#include "cub3d.h"

void	draw_floor(t_mlx_info *mlx_info)
{
	size_t	begin_y;
	size_t	end_y;
	size_t	begin_x;
	size_t	end_x;
	int		color;

	begin_y = mlx_info->win_height / 2;
	end_y = mlx_info->win_height;
	end_x = mlx_info->win_width;
	color = 0xB6BFC8;
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

void	draw_ceiling(t_mlx_info *mlx_info)
{
	size_t	begin_y;
	size_t	end_y;
	size_t	begin_x;
	size_t	end_x;
	int		color;

	begin_y = 0;
	end_y = mlx_info->win_height / 2;
	end_x = mlx_info->win_width;
	color = 0x3E434C;
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
}

void	ready_to_raycast(t_mlx_info *mlx_info, t_player_info *player_info, size_t i)
{
	player_info->camera_x = 2 / (double)mlx_info->win_width * i - 1;
	player_info->ray_x = player_info->dir_x + player_info->plane_x * player_info->camera_x;
	player_info->ray_y = player_info->dir_y + player_info->plane_y * player_info->camera_x;
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
	get_raycast_vector(player_info); // vector means each x and y step (scalar) and side (direction)
}

void	raycast_until_hit_wall(t_player_info *player_info, t_map_info *map_info)
{
	int		hit;

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
		if (map_info->map[player_info->map_y][player_info->map_x] == '1')
			hit = 1;
	}
}

size_t	get_wall_height(t_player_info *player_info)
{
	if (player_info->wall_side == NORTH || player_info->wall_side == SOUTH)
		player_info->perpendicular_distance_to_wall = player_info->side_y - player_info->delta_y;
	else // player_info->wall_side == WEST || EAST
		player_info->perpendicular_distance_to_wall = player_info->side_x - player_info->delta_x;
	return ((int)(WALL_SIZE_WEIGHT / player_info->perpendicular_distance_to_wall));
}

int	get_color(t_texture_info *texture_info, t_player_info *player_info, int tex_x, int tex_y)
{
	if (player_info->wall_side == NORTH)
		return (*(unsigned int *)(texture_info->north_img.addr + (tex_y * 256) + (tex_x * (32 / 8))));
	else if (player_info->wall_side == SOUTH)
		return (*(unsigned int *)(texture_info->south_img.addr + (tex_y * 256) + (tex_x * (32 / 8))));
	else if (player_info->wall_side == WEST)
		return (*(unsigned int *)(texture_info->west_img.addr + (tex_y * 256) + (tex_x * (32 / 8))));
	else // (player_info->wall_side == EAST)
		return (*(unsigned int *)(texture_info->east_img.addr + (tex_y * 256) + (tex_x * (32 / 8))));
}

void	get_tex_width_and_height(t_draw_info *draw_info, int wall_side, t_texture_info *texture_info)
{
	if (wall_side == NORTH)
	{
		draw_info->tex_width = texture_info->north_tex_width;
		draw_info->tex_height = texture_info->north_tex_height;
	}
	else if (wall_side == SOUTH)
	{
		draw_info->tex_width = texture_info->south_tex_width;
		draw_info->tex_height = texture_info->south_tex_height;
	}
	else if (wall_side == WEST)
	{
		draw_info->tex_width = texture_info->west_tex_width;
		draw_info->tex_height = texture_info->west_tex_height;
	}
	else // (wall_side == EAST)
	{
		draw_info->tex_width = texture_info->east_tex_width;
		draw_info->tex_height = texture_info->east_tex_height;
	}
}

void	draw_vertical_line(t_mlx_info *mlx_info, t_player_info *player_info, t_map_info *map_info, size_t wall_height, size_t i)
{
	t_draw_info	info;

	// Side depend on your direciton. Must be fixed.
	if (player_info->wall_side == NORTH || player_info->wall_side == SOUTH)
		info.wall_x = player_info->pos_x + player_info->perpendicular_distance_to_wall * player_info->ray_x;
	else
		info.wall_x = player_info->pos_y + player_info->perpendicular_distance_to_wall * player_info->ray_y;
	info.wall_x -= floor(info.wall_x);

	get_tex_width_and_height(&info, player_info->wall_side, &map_info->texture_info);
	info.tex_x = (int)(info.wall_x * (double)info.tex_width);
//	if ((player_info->wall_side == NORTH || player_info->wall_side == SOUTH) && player_info->ray_x > 0)
//		tex_x = map_info->tex_width - tex_x - 1;
//	else if ((player_info->wall_side == WEST || player_info->wall_side == EAST) && player_info->ray_y < 0)
//		tex_x = map_info->tex_width - tex_x - 1;
	info.begin_x = i;
	info.begin_y = (mlx_info->win_height / 2) - (wall_height / 2);
	if (info.begin_y < 0)
		info.begin_y = 0;

	info.step = 1.0 * info.tex_height / wall_height;
//	tex_pos = begin_y;
	info.tex_pos = (info.begin_y - mlx_info->win_height / 2 + wall_height / 2) * info.step;

	info.current_height = 0;
//	tex_y = tex_pos;
	while (info.current_height < wall_height)
	{
		if (info.begin_y >= (int)mlx_info->win_height)
			break ;
		info.tex_y = (int)info.tex_pos;// & (map_info->tex_height - 1);
		info.tex_pos += info.step;
		info.tex_color = get_color(&map_info->texture_info, player_info, info.tex_x, info.tex_y);
		my_mlx_pixel_put(&mlx_info->img_data, info.begin_x, info.begin_y++, info.tex_color);
		info.current_height++;
	}
}

void	draw_loop(t_mlx_info *mlx_info, t_map_info *map_info, t_player_info *player_info)
{
	size_t	i;
	size_t	wall_height;

	i = 0;
	draw_floor(mlx_info);
	draw_ceiling(mlx_info);
	while(i < mlx_info->win_width)
	{
		ready_to_raycast(mlx_info, player_info, i);
		raycast_until_hit_wall(player_info, map_info);
		wall_height = get_wall_height(player_info);
		draw_vertical_line(mlx_info, player_info, map_info, wall_height, i);
		i++;
	}
}
