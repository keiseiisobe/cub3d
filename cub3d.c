#include "include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_mlx_info	mlx_info;
	t_map_info	map_info;

// arg.c
	is_arg_valid(argc, argv);

// get_map.c
	get_map_info(&map_info, argv[1]);

// init.c
	initialize_mlx(&mlx_info);

// draw.c
	game_loop(&mlx_info, &map_info);
}
