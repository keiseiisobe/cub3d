#include "include/cub3d.h"

void	handle_error(bool is_error)
{
	if (is_error && errno != 0)
	{
		perror("cub3d");
		exit(EXIT_FAILURE);
	}
	else if (is_error && errno == 0)
	{
		printf("cub3d: Unknown error\n");
		exit(EXIT_FAILURE);
	}
}

void	put_my_error(const char *msg)
{
	int	i;

	i = 0;
	while (msg[i] != '\0')
	{
		write(2, &msg[i], 1);
		i++;
	}
}