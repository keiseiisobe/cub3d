/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:21:32 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/12 18:48:38 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub3d	info;

	is_arg_valid(argc, argv);
	get_map_info(&info.map_info, argv[1]);
	get_player_initial_info(&info.player_info, &info.map_info);
	initialize_mlx(&info.mlx_info);
	initialize_texture(&info);
	game(&info);
	mlx_hook(info.mlx_info.mlx_win, 2, 0, event_handler, &info);
	mlx_hook(info.mlx_info.mlx_win, 17, 0, x_bottun_handler, &info);
	mlx_loop(info.mlx_info.mlx);
}
