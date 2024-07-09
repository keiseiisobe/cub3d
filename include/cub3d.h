#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>

//# include "../minilibx_mms_20200219/mlx.h"
# include "mlx.h"

# include "xmalloc.h"
# include "get_next_line.h"
# include "libft.h"

# define WALL_SIZE_WEIGHT 200

# define ESC 53

# define MAX_MAP_SIZE 500

# define ONE_STEP 0.05

# define FORWARD 1
# define BACKWARD 2
# define LEFT 3
# define RIGHT 4

# define DEBUG 1
//# define DEBUG 0

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_mlx_info
{
	void	*mlx;
	void	*mlx_win;
	size_t	win_width;
	size_t	win_height;
	t_data	img_data;
}	t_mlx_info;

typedef struct	s_map_info
{
	char	**input_;
	size_t	input_height;

	char	**map;
	size_t	map_start_index;
	size_t	map_height;
	size_t	map_width;


	char	*no_texture_; // North
	char	*so_texture_; // South
	char	*we_texture_; // West
	char	*ea_texture_; // East
	int		ceiling_color[3]; // Ceiling
	int		floor_color[3]; // Floor
}	t_map_info;

enum wall_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct s_player_info
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_x;
	double	ray_y;
	size_t	map_x;
	size_t	map_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	int		wall_side;
	double	perpendicular_distance_to_wall;
}	t_player_info;

// use it in hook handler
typedef struct	s_cub3d
{
	t_map_info		map_info;
	t_mlx_info		mlx_info;
	t_player_info	player_info;
}	t_cub3d;

// arg.c
void	is_arg_valid(int argc, char *argv[]);

// get_map.c
void	get_map_info(t_map_info *map_info, char *filename);
size_t	get_input_height(char *filename);
char	**get_input(char *filename, size_t height);

// get_player.c
void	get_player_initial_info(t_player_info *player_info, t_map_info *map_info);

// init.c
void	initialize_mlx(t_mlx_info *mlx_info);

// game.c
void	game(t_cub3d *info);

// draw.c
void	draw_loop(t_mlx_info *mlx_info, t_map_info *map_info, t_player_info *player_info);

// mlx_utils.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

// event.c
int		event_handler(int keycode, t_cub3d *info);
int		X_bottun_handler(t_cub3d *info);

// move.c
void	walk_forward(t_player_info *player_info, char **map);
void	walk_backward(t_player_info *player_info, char **map);
void	walk_left(t_player_info *player_info, char **map);
void	walk_right(t_player_info *player_info, char **map);
void	turn_left(t_player_info *player_info);
void	turn_right(t_player_info *player_info);

// error.c
void	handle_error(bool is_error);

#endif
