/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:55:35 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 19:08:24 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_map_surrounded(char **mp, size_t h, size_t w)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (mp[i])
	{
		j = 0;
		while (mp[i][j])
		{
			if (mp[i][j] == PADDING)
			{
				if (i > 1 && mp[i - 1][j] != '1' && mp[i - 1][j] != PADDING)
					return (false);
				if (i < h && mp[i + 1][j] != '1' && mp[i + 1][j] != PADDING)
					return (false);
				if (j > 1 && mp[i][j - 1] != '1' && mp[i][j - 1] != PADDING)
					return (false);
				if (j < w && mp[i][j + 1] != '1' && mp[i][j + 1] != PADDING)
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	char_check(char **map_padding_)
{
	size_t	i;
	size_t	j;
	size_t	player_count;

	i = 0;
	player_count = 0;
	while (map_padding_[i])
	{
		j = 0;
		while (map_padding_[i][j])
		{
			if (map_padding_[i][j] == 'N' || map_padding_[i][j] == 'S'
				|| map_padding_[i][j] == 'W' || map_padding_[i][j] == 'E')
				player_count++;
			else if (map_padding_[i][j] != '1' && map_padding_[i][j] != '0'
				&& map_padding_[i][j] != PADDING)
				return (false);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (false);
	return (true);
}

bool	is_valid_map(char **map, size_t height)
{
	char	**map_padding_;
	size_t	width;

	width = get_map_width(map);
	if (width > MAX_MAP_SIZE || height > MAX_MAP_SIZE)
	{
		put_my_error("cub3d: Error: Invalid map\n");
		return (false);
	}
	map_padding_ = add_padding(map, height, width);
	if (!is_map_surrounded(map_padding_, height, width)
		|| !char_check(map_padding_))
	{
		free_2d_char(map_padding_);
		put_my_error("cub3d: Error: Invalid map\n");
		return (false);
	}
	free_2d_char(map_padding_);
	return (true);
}
