/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 02:12:58 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 02:16:54 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_left(t_player_info *player_info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player_info->dir_x;
	player_info->dir_x = player_info->dir_x * cos(ONE_STEP * -1)
		- player_info->dir_y * sin(ONE_STEP * -1);
	player_info->dir_y = old_dir_x * sin(ONE_STEP * -1)
		+ player_info->dir_y * cos(ONE_STEP * -1);
	old_plane_x = player_info->plane_x;
	player_info->plane_x = player_info->plane_x * cos(ONE_STEP * -1)
		- player_info->plane_y * sin(ONE_STEP * -1);
	player_info->plane_y = old_plane_x * sin(ONE_STEP * -1)
		+ player_info->plane_y * cos(ONE_STEP * -1);
}

void	turn_right(t_player_info *player_info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player_info->dir_x;
	player_info->dir_x = player_info->dir_x * cos(ONE_STEP)
		- player_info->dir_y * sin(ONE_STEP);
	player_info->dir_y = old_dir_x * sin(ONE_STEP)
		+ player_info->dir_y * cos(ONE_STEP);
	old_plane_x = player_info->plane_x;
	player_info->plane_x = player_info->plane_x * cos(ONE_STEP)
		- player_info->plane_y * sin(ONE_STEP);
	player_info->plane_y = old_plane_x * sin(ONE_STEP)
		+ player_info->plane_y * cos(ONE_STEP);
}

void	update_pos(t_player_info *player_info,
		double *pos_x, double *pos_y, int step_direction)
{
	if (step_direction == FORWARD)
	{
		*pos_x += player_info->dir_x * (ONE_STEP * 3);
		*pos_y += player_info->dir_y * (ONE_STEP * 3);
	}
	else if (step_direction == BACKWARD)
	{
		*pos_x -= player_info->dir_x * (ONE_STEP * 3);
		*pos_y -= player_info->dir_y * (ONE_STEP * 3);
	}
	else if (step_direction == RIGHT)
	{
		*pos_x -= player_info->dir_y * (ONE_STEP * 3);
		*pos_y += player_info->dir_x * (ONE_STEP * 3);
	}
	else if (step_direction == LEFT)
	{
		*pos_x += player_info->dir_y * (ONE_STEP * 3);
		*pos_y -= player_info->dir_x * (ONE_STEP * 3);
	}
}

bool	is_not_wall(t_player_info *player_info, char **map, int step_direction)
{
	double	pos_x;
	double	pos_y;
	size_t	map_x;
	size_t	map_y;

	pos_x = player_info->pos_x;
	pos_y = player_info->pos_y;
	update_pos(player_info, &pos_x, &pos_y, step_direction);
	map_x = (size_t)pos_x;
	map_y = (size_t)pos_y;
	return (map[map_y][map_x] != '1');
}
