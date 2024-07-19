/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 02:12:47 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 02:15:51 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

void	walk_right(t_player_info *player_info, char **map)
{
	if (is_not_wall(player_info, map, RIGHT))
	{
		player_info->pos_x -= player_info->dir_y * (ONE_STEP * 3);
		player_info->pos_y += player_info->dir_x * (ONE_STEP * 3);
	}
}
