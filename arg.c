#include "../include/cub3d.h"

void	is_arg_valid(int argc, char *argv[])
{
	(void)argv;
	if (argc != 2)
	{
		ft_err_printf("cub3d: Notice: ./cub3d [filename]\n");
		exit(EXIT_SUCCESS);
	}
	// is_file_valid(); ex. suffix, empty, surrounded by wall
}
