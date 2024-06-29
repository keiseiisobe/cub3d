NAME = cub3d
SRCS = main.c \
		get_map.c \
		get_player.c \
		event.c \
		move.c \
		init_mlx.c \
		game.c \
		draw.c \
		error.c \
		arg.c \
		xmalloc.c \
		mlx_utils.c \
		libft/get_next_line.c \
		libft/get_next_line_utils.c
OBJS_DIR = object
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_LIB = -L./ -lmlx
MLX_INCLUDE = -Imlx
LINK_FW = -framework OpenGL -framework AppKit

vpath % error libft

$(OBJS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLX_LIB) $(LINK_FW) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
