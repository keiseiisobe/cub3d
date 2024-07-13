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

void	ready_to_raycast(t_mlx_info *mlx_info, t_player_info *player_info, size_t i)
{
	player_info->camera_x = 2 / (double)mlx_info->win_width * i - 1;
	player_info->ray_x = player_info->dir_x + player_info->plane_x * player_info->camera_x; // it depends on the player direction.
	player_info->ray_y = player_info->dir_y + player_info->plane_y * player_info->camera_x; // N or S or W or E. in this case, N.
//		printf("ray_x: %f   ray_y: %f\n", player_info->ray_x, player_info->ray_y);
	player_info->map_x = (size_t)player_info->pos_x;
	player_info->map_y = (size_t)player_info->pos_y;
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

int	get_wall_color(int wall_side, t_map_info *map_info)
{
	(void)map_info;
	if (wall_side == NORTH)
		return (0x00FF0000); // red
	else if (wall_side == SOUTH)
		return (0x0000FF00); // pink
	else if (wall_side == WEST)
		return (0x000000FF); // blue
	else // wall_side == EAST
		return (0x00FFFF00); // green
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_vertical_line(t_mlx_info *mlx_info, t_player_info *player_info, t_map_info *map_info, size_t wall_height, size_t i)
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		begin_x;
	int		begin_y;
	size_t	current_height;
	int		tex_color;

	// Side depend on your direciton. Must be fixed.
	if (player_info->wall_side == NORTH || player_info->wall_side == SOUTH)
		wall_x = player_info->pos_x + player_info->perpendicular_distance_to_wall * player_info->ray_x;
	else
		wall_x = player_info->pos_y + player_info->perpendicular_distance_to_wall * player_info->ray_y;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)map_info->tex_width);
//	printf("wall_x: %f\n", wall_x);
//	if ((player_info->wall_side == NORTH || player_info->wall_side == SOUTH) && player_info->ray_x > 0)
//		tex_x = map_info->tex_width - tex_x - 1;
//	else if ((player_info->wall_side == WEST || player_info->wall_side == EAST) && player_info->ray_y < 0)
//		tex_x = map_info->tex_width - tex_x - 1;
	begin_x = i;
	begin_y = (mlx_info->win_height / 2) - (wall_height / 2);
	if (begin_y < 0)
		begin_y = 0;

	step = 1.0 * map_info->tex_height / wall_height;
//	tex_pos = begin_y;
	tex_pos = (begin_y - mlx_info->win_height / 2 + wall_height / 2) * step;

	current_height = 0;
//	tex_y = tex_pos;
	while (current_height < wall_height)
	{
//		printf("begin_y: %zu\n", begin_y);
		if (begin_y >= (int)mlx_info->win_height)
			break ;
		tex_y = (int)tex_pos;// & (map_info->tex_height - 1);
//		printf("tex_pos: %f\n", tex_pos);
//		printf("tex_y: %d\n", tex_y);
		tex_pos += step;
		if (player_info->wall_side == NORTH)
			tex_color = *(unsigned int *)(map_info->north_texture_ + (tex_y * 256) + (tex_x * (32 / 8)));
		else if (player_info->wall_side == SOUTH)
			tex_color = *(unsigned int *)(map_info->south_texture_ + (tex_y * 256) + (tex_x * (32 / 8)));
		else if (player_info->wall_side == WEST)
			tex_color = *(unsigned int *)(map_info->west_texture_ + (tex_y * 256) + (tex_x * (32 / 8)));
		else // (player_info->wall_side == EAST)
			tex_color = *(unsigned int *)(map_info->east_texture_ + (tex_y * 256) + (tex_x * (32 / 8)));
		my_mlx_pixel_put(&mlx_info->img_data, begin_x, begin_y++, tex_color);
		current_height++;
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
//		color = get_wall_color(player_info->wall_side, map_info);
		draw_vertical_line(mlx_info, player_info, map_info, wall_height, i);
		i++;
	}
}
