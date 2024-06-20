#include "../include/error.h"

void	handle_error(bool is_error)
{
	if (is_error && errno != 0)
	{
		perror("cub3d");
		exit(EXIT_FAILURE);
	}
	else if (is_error && errno == 0)
	{
		ft_err_printf("cub3d: Unknown error\n");
		exit(EXIT_FAILURE);
	}
}
