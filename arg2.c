/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:23:59 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 15:34:49 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_char(const char *str, char target)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == target)
			count++;
		str++;
	}
	return (count);
}

bool	is_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

bool	is_valid_rgb_format(char *str)
{
	char	**rgb;

	if (count_char(str, ',') != 2 || ft_strlen(str) < 5 || ft_strlen(str) > 12)
	{
		put_my_error("cub3d: Error: Invalid RGB format\n");
		return (false);
	}
	str[ft_strlen(str) - 1] = '\0';
	rgb = ft_split(str, ',');
	if ((rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
		|| (!is_digit(rgb[0]) || !is_digit(rgb[1]) || !is_digit(rgb[2])))
	{
		put_my_error("cub3d: Error: Invalid RGB format\n");
		free_2d_char(rgb);
		return (false);
	}
	if (ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) > 255
		|| ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[2]) < 0)
	{
		put_my_error("cub3d: Error: Invalid RGB format\n");
		free_2d_char(rgb);
		return (false);
	}
	free_2d_char(rgb);
	return (true);
}
