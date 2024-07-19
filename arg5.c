/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:32:02 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 19:06:51 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	error_with_free2d(char **s, bool should_free, bool should_error)
{
	if (should_free)
		free_2d_char(s);
	if (should_error)
		put_my_error("cub3d: Error: Invalid input\n");
	return (false);
}

bool	is_valid_wall_format(char **s, unsigned int *flag6)
{
	if (s[0][0] == 'N' && s[0][1] == 'O' && !(*flag6 & 0b100000))
		*flag6 |= 0b100000;
	else if (s[0][0] == 'S' && s[0][1] == 'O' && !(*flag6 & 0b010000))
		*flag6 |= 0b010000;
	else if (s[0][0] == 'W' && s[0][1] == 'E' && !(*flag6 & 0b001000))
		*flag6 |= 0b001000;
	else if (s[0][0] == 'E' && s[0][1] == 'A' && !(*flag6 & 0b000100))
		*flag6 |= 0b000100;
	else
		return (error_with_free2d(s, true, true));
	if (!is_usable_file(s[1]))
		return (error_with_free2d(s, true, false));
	return (true);
}

bool	is_valid_cf_format(char **s, unsigned int *flag6)
{
	if (s[0][0] == 'F' && !(*flag6 & 0b000010))
		*flag6 |= 0b000010;
	else if (s[0][0] == 'C' && !(*flag6 & 0b000001))
		*flag6 |= 0b000001;
	else
		return (error_with_free2d(s, true, true));
	if (!is_valid_rgb_format(s[1]))
		return (false);
	return (true);
}

bool	is_valid_non_map_info_format(char **s, unsigned int *flag6)
{
	if (ft_strlen(s[0]) == 2)
	{
		if (!is_valid_wall_format(s, flag6))
			return (false);
	}
	else if (ft_strlen(s[0]) == 1)
	{
		if (!is_valid_cf_format(s, flag6))
			return (false);
	}
	else
		return (error_with_free2d(s, true, true));
	return (true);
}

bool	is_valid_non_map_info(char **input_, int *map_start_index)
{
	size_t			i;
	char			**s;
	unsigned int	flag6;

	flag6 = 0b000000;
	i = -1;
	while (input_[++i] && flag6 != 0b111111)
	{
		if (input_[i][0] == '\n')
			continue ;
		s = ft_split(input_[i], ' ');
		if (s[0] == NULL || s[1] == NULL || s[2] != NULL)
			return (error_with_free2d(s, true, true));
		if (!is_valid_non_map_info_format(s, &flag6))
			return (false);
		free_2d_char(s);
	}
	if (flag6 != 0b111111)
		return (error_with_free2d(NULL, false, true));
	while (input_[i][0] == '\n')
		i++;
	*map_start_index = i;
	return (true);
}
