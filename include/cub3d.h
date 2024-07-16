/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 02:07:58 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2024/07/16 15:05:33 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# include "mlx.h"

# include "get_next_line.h"
# include "libft.h"

# define WALL_SIZE_WEIGHT 800

# define ESC 53

# define MAX_MAP_SIZE 500

# define ONE_STEP 0.05

# define FORWARD 1
# define BACKWARD 2
# define LEFT 3
# define RIGHT 4

# define DEBUG 1
//# define DEBUG 0

typedef enum e_wall_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_wall_side;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx_info
{
	void	*mlx;
	void	*mlx_win;
	size_t	win_width;
	size_t	win_height;
	t_data	img_data;
}	t_mlx_info;

typedef struct s_texture_info
{
	void	*mlx;

	char	*north_tex_filename_;
	int		north_tex_w;
	int		north_tex_h;
	bool	north_is_png;
	t_data	north_img;

	char	*south_tex_filename_;
	int		south_tex_w;
	int		south_tex_h;
	bool	south_is_png;
	t_data	south_img;

	char	*west_tex_filename_;
	int		west_tex_w;
	int		west_tex_h;
	bool	west_is_png;
	t_data	west_img;

	char	*east_tex_filename_;
	int		east_tex_w;
	int		east_tex_h;
	bool	east_is_png;
	t_data	east_img;
}	t_texture_info;

typedef struct s_map_info
{
	char			**input_;
	size_t			input_height;

	char			**map;
	size_t			map_start_index;
	size_t			map_height;
	size_t			map_width;

	t_texture_info	texture_info;
	unsigned char	ceiling_color[4];
	unsigned char	floor_color[4];
}	t_map_info;

typedef struct s_player_info
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_x;
	double		ray_y;
	size_t		map_x;
	size_t		map_y;
	double		side_x;
	double		side_y;
	double		delta_x;
	double		delta_y;
	int			step_x;
	int			step_y;
	t_wall_side	wall_side;
	double		perpendicular_distance_to_wall;
}	t_player_info;

typedef struct s_cub3d
{
	t_mlx_info		mlx_info;
	t_map_info		map_info;
	t_player_info	player_info;
}	t_cub3d;

typedef struct s_draw_info
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	int		tex_width;
	int		tex_height;
	double	step;
	int		begin_x;
	int		begin_y;
	size_t	current_height;
	int		tex_color;
}	t_draw_info;

// arg.c
void	is_arg_valid(int argc, char *argv[]);
void	free_2d_char(char **str);

// get_map.c
void	get_map_info(t_map_info *map_info, char *filename);

// get_map2.c
size_t	get_input_height(char *filename);
char	**get_input(char *filename, size_t height);


// get_player.c
void	get_player_initial_info(t_player_info *player_info,
			t_map_info *map_info);

// init_mlx.c
void	initialize_mlx(t_mlx_info *mlx_info);

// init_texture.c
void	initialize_texture(t_cub3d *info);

// game.c
void	game(t_cub3d *info);

// draw.c
void	draw_loop(t_cub3d *info);

// draw2.c
void	draw_vertical_line(t_cub3d *info, size_t wall_height, size_t i);
size_t	get_wall_height(t_player_info *player_info);

// mlx_utils.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

// event.c
int		event_handler(int keycode, t_cub3d *info);
int		x_bottun_handler(t_cub3d *info);

// move.c
void	walk_forward(t_player_info *player_info, char **map);
void	walk_backward(t_player_info *player_info, char **map);
void	walk_left(t_player_info *player_info, char **map);
void	walk_right(t_player_info *player_info, char **map);

// move2.c
void	turn_left(t_player_info *player_info);
void	turn_right(t_player_info *player_info);
bool	is_not_wall(t_player_info *player_info,
			char **map, int step_direction);

// xmalloc.c
void	*xmalloc(size_t size);
void	destroy_all_image(t_cub3d *info);
void	free_all(t_map_info *map_info);


// error.c
void	handle_error(bool is_error);
void	put_my_error(const char *msg);

// debug.c
void	print_non_map_info(t_map_info *map_info);
void	print_map_info(t_map_info *map_info);

#endif
