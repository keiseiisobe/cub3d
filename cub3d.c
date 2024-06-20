#include "include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_mlx_info	mlx_info;
	t_map_info	map_info;
	t_param		param;

// arg.c
	is_arg_valid(argc, argv);

// get_map.c
	get_map_info(&map_info, argv[1]);

// init.c
	initialize_mlx(&mlx_info);

// draw.c
	param.mlx_info = &mlx_info;
	param.map_info = &map_info;
	game(&param);

// hook and loop
	mlx_hook(mlx_info.mlx_win, 2, 0, hook_handler, &param); // some memory that should be freed will be taken as parameter.
	mlx_loop(mlx_info.mlx);
}
