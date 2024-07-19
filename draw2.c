/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:03:56 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 15:06:09 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	else if (player_info->wall_side == EAST)
		return (*(unsigned int *)(texture_info->east_img.addr
			+ (tex_y * texture_info->east_img.line_length)
			+ (tex_x * (texture_info->east_img.bits_per_pixel / 8))));
	return (0);
}

void	get_tex_width_and_height(t_draw_info *draw_info,
		int wall_side, t_texture_info *texture_info)
{
	if (wall_side == NORTH)
	{
		draw_info->tex_width = texture_info->north_tex_w;
		draw_info->tex_height = texture_info->north_tex_h;
	}
	else if (wall_side == SOUTH)
	{
		draw_info->tex_width = texture_info->south_tex_w;
		draw_info->tex_height = texture_info->south_tex_h;
	}
	else if (wall_side == WEST)
	{
		draw_info->tex_width = texture_info->west_tex_w;
		draw_info->tex_height = texture_info->west_tex_h;
	}
	else if (wall_side == EAST)
	{
		draw_info->tex_width = texture_info->east_tex_w;
		draw_info->tex_height = texture_info->east_tex_h;
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

	draw_info.begin_x = i;
	draw_info.begin_y = (info->mlx_info.win_height / 2) - (wall_height / 2);
	if (draw_info.begin_y < 0)
		draw_info.begin_y = 0;
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
		draw_info.tex_y = (int)draw_info.tex_pos;
		draw_info.tex_pos += draw_info.step;
		draw_info.tex_color = get_color(&info->map_info.texture_info,
				&info->player_info, draw_info.tex_x, draw_info.tex_y);
		my_mlx_pixel_put(&info->mlx_info.img_data, draw_info.begin_x,
			draw_info.begin_y++, draw_info.tex_color);
		draw_info.current_height++;
	}
}

size_t	get_wall_height(t_player_info *player_info)
{
	if (player_info->wall_side == NORTH || player_info->wall_side == SOUTH)
		player_info->perpendicular_distance_to_wall
			= player_info->side_y - player_info->delta_y;
	else if (player_info->wall_side == WEST || player_info->wall_side == EAST)
		player_info->perpendicular_distance_to_wall
			= player_info->side_x - player_info->delta_x;
	return ((int)(WALL_SIZE_WEIGHT
		/ player_info->perpendicular_distance_to_wall));
}
