/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 02:20:25 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 19:07:00 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_usable_file(char *fp)
{
	int	fd;

	fp[ft_strlen(fp) - 1] = '\0';
	if (ft_strlen(fp) < 5 || (ft_strncmp(fp + ft_strlen(fp) - 4, ".xpm", 4)
			&& ft_strncmp(fp + ft_strlen(fp) - 4, ".png", 4)))
	{
		put_my_error("cub3d: Error: Invalid file path\n");
		return (false);
	}
	fd = open(fp, O_RDONLY);
	if (fd == -1)
	{
		perror("cube3d: Error:");
		return (false);
	}
	close(fd);
	return (true);
}

bool	is_valid_cub_file(char **input_, size_t input_height)
{
	char	**map;
	int		map_start_index;

	if (!is_valid_non_map_info(input_, &map_start_index))
		return (false);
	map = &input_[map_start_index - 1];
	if (!is_valid_map(map, input_height - map_start_index))
		return (false);
	return (true);
}

void	is_arg_valid(int argc, char *argv[])
{
	char	**input_;
	size_t	input_height;

	(void)argv;
	if (argc != 2)
	{
		put_my_error("cub3d: Notice: ./cub3d [filename]\n");
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(argv[1]) < 5
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		put_my_error("cub3d: Error: Invalid file path\n");
		exit(EXIT_SUCCESS);
	}
	input_height = get_input_height(argv[1]);
	input_ = get_input(argv[1], input_height);
	if (!is_valid_cub_file(input_, input_height))
	{
		free_2d_char(input_);
		exit(EXIT_SUCCESS);
	}
	free_2d_char(input_);
	return ;
}
