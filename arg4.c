/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:08:28 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 19:21:23 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	padding_full_line(char **map_padding_, size_t i,
	size_t *j, size_t width)
{
	while (++(*j) < width + 1)
		map_padding_[i][*j] = PADDING;
	map_padding_[i][*j] = '\0';
	return (true);
}

char	choice_padding_map_letter(char c)
{
	if (c == '\n' || c == '\0')
		return (PADDING);
	if (c != ' ')
		return (c);
	return (PADDING);
}

char	**add_padding(char **map, size_t height, size_t width)
{
	char	**map_padding_;
	size_t	i;
	size_t	j;

	map_padding_ = xmalloc(sizeof(char *) * (height + 3));
	i = -1;
	while (++i < height + 2)
	{
		map_padding_[i] = xmalloc(sizeof(char) * (width + 3));
		j = 0;
		map_padding_[i][j] = PADDING;
		if ((i == 0 || i == height + 1)
			&& padding_full_line(map_padding_, i, &j, width))
			continue ;
		while (++j < width + 1)
		{
			map_padding_[i][j] = choice_padding_map_letter(map[i][j - 1]);
			if (map[i][j - 1] == '\n' || map[i][j - 1] == '\0')
				break ;
		}
		padding_full_line(map_padding_, i, &j, width);
	}
	map_padding_[i] = NULL;
	print_padding_map(map_padding_);
	return (map_padding_);
}
