#include "cub3d.h"

bool	is_not_wall(t_player_info *player_info, char **map, int step_direction)
{
	double	pos_x;
	double	pos_y;
	size_t	map_x;
	size_t	map_y;

	pos_x = player_info->pos_x;
	pos_y = player_info->pos_y;
	if (step_direction == FORWARD)
	{
		pos_x += player_info->dir_x * (ONE_STEP * 3);
		pos_y += player_info->dir_y * (ONE_STEP * 3);
	}
	else if (step_direction == BACKWARD)
	{
		pos_x -= player_info->dir_x * (ONE_STEP * 3);
		pos_y -= player_info->dir_y * (ONE_STEP * 3);
	}
	else if (step_direction == RIGHT)
	{
		pos_x -= player_info->dir_y * (ONE_STEP * 3);
		pos_y += player_info->dir_x * (ONE_STEP * 3);
	}
	else if (step_direction == LEFT)
	{
		pos_x += player_info->dir_y * (ONE_STEP * 3);
		pos_y -= player_info->dir_x * (ONE_STEP * 3);
	}
	map_x = (size_t)pos_x;
	map_y = (size_t)pos_y;
	return (map[map_y][map_x] != '1');
}

void	walk_forward(t_player_info *player_info, char **map)
{
	if (is_not_wall(player_info, map, FORWARD))
	{
		player_info->pos_x += player_info->dir_x * (ONE_STEP * 3);
		player_info->pos_y += player_info->dir_y * (ONE_STEP * 3);
	}
}

void	walk_backward(t_player_info *player_info, char **map)
{
	if (is_not_wall(player_info, map, BACKWARD))
	{
		player_info->pos_x -= player_info->dir_x * (ONE_STEP * 3);
		player_info->pos_y -= player_info->dir_y * (ONE_STEP * 3);
	}
}

void	walk_left(t_player_info *player_info, char **map)
{
	if (is_not_wall(player_info, map, LEFT))
	{
		player_info->pos_x += player_info->dir_y * (ONE_STEP * 3);
		player_info->pos_y -= player_info->dir_x * (ONE_STEP * 3);
	}
/*
	if (player_info->dir_x == 0 && player_info->dir_y == -1) // North
	{
		if (is_not_wall(player_info, map, ONE_STEP * -1, X))
			player_info->pos_x += ONE_STEP * -1;
	}
	else if (player_info->dir_x == 0 && player_info->dir_y == 1) // South
	{
		if (is_not_wall(player_info, map, ONE_STEP, X))
			player_info->pos_x += ONE_STEP;
	}
	else if (player_info->dir_x == -1 && player_info->dir_y == 0) // West
	{
		if (is_not_wall(player_info, map, ONE_STEP, Y))
			player_info->pos_y += ONE_STEP;
	}
	else // (player_info->dir_x == 1 && player_info->dir_y == 0) // East
	{
		if (is_not_wall(player_info, map, ONE_STEP * -1, Y))
			player_info->pos_y += ONE_STEP * -1;
	}
*/
}

void	walk_right(t_player_info *player_info, char **map)
{
	if (is_not_wall(player_info, map, RIGHT))
	{
		player_info->pos_x -= player_info->dir_y * (ONE_STEP * 3);
		player_info->pos_y += player_info->dir_x * (ONE_STEP * 3);
	}
/*
	if (player_info->dir_x == 0 && player_info->dir_y == -1) // North
	{
		if (is_not_wall(player_info, map, ONE_STEP, X))
			player_info->pos_x += ONE_STEP;
	}
	else if (player_info->dir_x == 0 && player_info->dir_y == 1) // South
	{
		if (is_not_wall(player_info, map, ONE_STEP * -1, X))
			player_info->pos_x += ONE_STEP * -1;
	}
	else if (player_info->dir_x == -1 && player_info->dir_y == 0) // West
	{
		if (is_not_wall(player_info, map, ONE_STEP * -1, Y))
			player_info->pos_y += ONE_STEP * -1;
	}
	else // (player_info->dir_x == 1 && player_info->dir_y == 0) // East
	{
		if (is_not_wall(player_info, map, ONE_STEP, Y))
			player_info->pos_y += ONE_STEP;
	}
*/
}

void	turn_left(t_player_info *player_info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player_info->dir_x;
	player_info->dir_x = player_info->dir_x * cos(ONE_STEP * -1) - player_info->dir_y * sin(ONE_STEP * -1);
	player_info->dir_y = old_dir_x * sin(ONE_STEP * -1) + player_info->dir_y * cos(ONE_STEP * -1);
	old_plane_x = player_info->plane_x;
	player_info->plane_x = player_info->plane_x * cos(ONE_STEP * -1) - player_info->plane_y * sin(ONE_STEP * -1);
	player_info->plane_y = old_plane_x * sin(ONE_STEP * -1) + player_info->plane_y * cos(ONE_STEP * -1);
}

void	turn_right(t_player_info *player_info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player_info->dir_x;
	player_info->dir_x = player_info->dir_x * cos(ONE_STEP) - player_info->dir_y * sin(ONE_STEP);
	player_info->dir_y = old_dir_x * sin(ONE_STEP) + player_info->dir_y * cos(ONE_STEP);
	old_plane_x = player_info->plane_x;
	player_info->plane_x = player_info->plane_x * cos(ONE_STEP) - player_info->plane_y * sin(ONE_STEP);
	player_info->plane_y = old_plane_x * sin(ONE_STEP) + player_info->plane_y * cos(ONE_STEP);
}
