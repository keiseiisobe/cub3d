/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:47:45 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 15:55:10 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	get_input_height(char *filename)
{
	int		fd;
	char	*line;
	size_t	height;

	fd = open(filename, O_RDONLY);
	handle_error(fd < 0);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		height++;
	}
	close(fd);
	return (height);
}

char	**get_input(char *filename, size_t height)
{
	int		fd;
	char	*line;
	char	**input;
	size_t	i;

	fd = open(filename, O_RDONLY);
	handle_error(fd < 0);
	input = xmalloc((height + 1) * sizeof(char *));
	i = 0;
	while (i < height)
	{
		line = get_next_line(fd);
		input[i++] = ft_strdup(line);
		free(line);
	}
	input[i] = NULL;
	close(fd);
	return (input);
}

size_t	get_map_width(char **map)
{
	size_t	i;
	size_t	max_width;
	size_t	width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		width = ft_strlen(map[i]);
		if (width > max_width)
			max_width = width;
		i++;
	}
	return (max_width);
}
