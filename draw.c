#include "cub3d.h"

void	draw_floor(t_mlx_info *mlx_info, t_map_info *map_info)
{
	size_t	begin_y;
	size_t	end_y;
	size_t	begin_x;
	size_t	end_x;
	int		color;

	begin_y = mlx_info->win_height / 2;
	end_y = mlx_info->win_height;
	end_x = mlx_info->win_width;
	color = *(int *)map_info->floor_color;
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

void	draw_ceiling(t_mlx_info *mlx_info, t_map_info *map_info)
{
	size_t	begin_y;
	size_t	end_y;
	size_t	begin_x;
	size_t	end_x;
	int		color;

	begin_y = 0;
	end_y = mlx_info->win_height / 2;
	end_x = mlx_info->win_width;
	color = *(int *)map_info->ceiling_color;
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
	else // ray_x >= 0
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
	else // ray_y >= 0
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
	get_raycast_vector(player_info); // vector means each x and y step (scalar) and side (direction)
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
			break ;
	}
}

size_t	get_wall_height(t_player_info *player_info)
{
	if (player_info->wall_side == NORTH || player_info->wall_side == SOUTH)
		player_info->perpendicular_distance_to_wall
			= player_info->side_y - player_info->delta_y;
	else // player_info->wall_side == WEST || EAST
		player_info->perpendicular_distance_to_wall
			= player_info->side_x - player_info->delta_x;
	return ((int)(WALL_SIZE_WEIGHT
		/ player_info->perpendicular_distance_to_wall));
}

int	get_color(t_texture_info *texture_info, t_player_info *player_info,
	int tex_x, int tex_y)
{
	if (player_info->wall_side == NORTH)
		return (*(unsigned int *)(texture_info->north_img.addr
			+ (tex_y * texture_info->north_img.line_length)
			+ (tex_x * (texture_info->north_img.bits_per_pixel / 8))));
	else if (player_info->wall_side == SOUTH)
		return (*(unsigned int *)(texture_info->south_img.addr
			+ (tex_y * texture_info->south_img.line_length)
			+ (tex_x * (texture_info->south_img.bits_per_pixel / 8))));
	else if (player_info->wall_side == WEST)
		return (*(unsigned int *)(texture_info->west_img.addr
			+ (tex_y * texture_info->west_img.line_length)
			+ (tex_x * (texture_info->west_img.bits_per_pixel / 8))));
	else // (player_info->wall_side == EAST)
		return (*(unsigned int *)(texture_info->east_img.addr
			+ (tex_y * texture_info->east_img.line_length)
			+ (tex_x * (texture_info->east_img.bits_per_pixel / 8))));
}

void	get_tex_width_and_height(t_draw_info *draw_info,
		int wall_side, t_texture_info *texture_info)
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

void	get_wall_x(t_player_info *player_info, t_draw_info *info)
{
	if (player_info->wall_side == NORTH || player_info->wall_side == SOUTH)
		info->wall_x
			= player_info->pos_x
			+ player_info->perpendicular_distance_to_wall * player_info->ray_x;
	else
		info->wall_x
			= player_info->pos_y
			+ player_info->perpendicular_distance_to_wall * player_info->ray_y;
	if (player_info->wall_side == SOUTH || player_info->wall_side == WEST)
		info->wall_x = 1 - (info->wall_x - floor(info->wall_x));
	else
		info->wall_x -= floor(info->wall_x);
}

void	draw_vertical_line(t_cub3d *info, size_t wall_height, size_t i)
{
	t_draw_info	draw_info;

	// x and y in mlx image
	draw_info.begin_x = i;
	draw_info.begin_y = (info->mlx_info.win_height / 2) - (wall_height / 2);
	if (draw_info.begin_y < 0)
		draw_info.begin_y = 0;
	// x and y in texture
	get_wall_x(&info->player_info, &draw_info);
	get_tex_width_and_height(&draw_info, info->player_info.wall_side,
		&info->map_info.texture_info);
	draw_info.tex_x = (int)(draw_info.wall_x * (double)draw_info.tex_width);
	draw_info.step = 1.0 * draw_info.tex_height / wall_height;
	draw_info.tex_pos = (draw_info.begin_y - info->mlx_info.win_height / 2
			+ wall_height / 2) * draw_info.step;
	draw_info.current_height = 0;
	while (draw_info.current_height < wall_height
		&& draw_info.begin_y < (int)info->mlx_info.win_height)
	{
		draw_info.tex_y = (int)draw_info.tex_pos;// & (info->map_info->tex_height - 1);
		draw_info.tex_pos += draw_info.step;
		draw_info.tex_color = get_color(&info->map_info.texture_info,
				&info->player_info, draw_info.tex_x, draw_info.tex_y);
		my_mlx_pixel_put(&info->mlx_info.img_data, draw_info.begin_x,
			draw_info.begin_y++, draw_info.tex_color);
		draw_info.current_height++;
	}
}

void	draw_loop(t_cub3d *info)
{
	size_t	i;
	size_t	wall_height;

	i = 0;
	draw_floor(&info->mlx_info, &info->map_info);
	draw_ceiling(&info->mlx_info, &info->map_info);
	while (i < info->mlx_info.win_width)
	{
		ready_to_raycast(&info->mlx_info, &info->player_info, i);
		raycast_until_hit_wall(&info->player_info, &info->map_info);
		wall_height = get_wall_height(&info->player_info);
		draw_vertical_line(info, wall_height, i);
		i++;
	}
}
