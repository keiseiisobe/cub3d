#include "include/cub3d.h"

static bool	is_player(char map_elem)
{
	if (map_elem == 'N' || map_elem == 'S' || map_elem == 'W' || map_elem == 'E')
		return (true);
	return (false);
}

static void	get_player_direction(t_player_info *player_info, char player_direction)
{
	if (player_direction == 'N')
	{
		player_info->dir_x = 0;
		player_info->dir_y = -1;
	}
	else if (player_direction == 'S')
	{
		player_info->dir_x = 0;
		player_info->dir_y = 1;
	}
	else if (player_direction == 'W')
	{
		player_info->dir_x = -1;
		player_info->dir_y = 0;
	}
	else if (player_direction == 'E')
	{
		player_info->dir_x = 1;
		player_info->dir_y = 0;
	}
}

static void	get_player_position(t_player_info *player_info, t_map_info *map_info)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map_info->map_height)
	{
		x = 0;
		while (x < map_info->map_width)
		{
			// if there are no player ?? is it handled in init.c ?
			if (is_player(map_info->map[y][x]))
				break ;
			x++;
		}
		if (x != map_info->map_width)
			break ;
		y++;
	}
	player_info->pos_x = (double)x + 0.5;
	player_info->pos_y = (double)y + 0.5;
	get_player_direction(player_info, map_info->map[y][x]);
}

void	get_player_initial_info(t_player_info *player_info, t_map_info *map_info)
{
	get_player_position(player_info, map_info);
	if (player_info->dir_x == 0) // North or South
	{
		player_info->plane_x = 0.66;
		player_info->plane_y = 0;
	}
	else // West or East
	{
		player_info->plane_x = 0;
		player_info->plane_y = 0.66;
	}
}

void	game(t_param *param)
{
	t_player_info	player_info;

	get_player_initial_info(&player_info, param->map_info);
	draw_loop(param->mlx_info, param->map_info, &player_info);
	mlx_put_image_to_window(param->mlx_info->mlx, param->mlx_info->mlx_win, param->mlx_info->img_data.img, 0, 0);
}
