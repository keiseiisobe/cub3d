NAME = cub3d
SRCS = cub3d.c get_map.c init_mlx.c game.c draw.c error.c\
		arg.c xmalloc.c mlx_utils.c\
		get_next_line.c get_next_line_utils.c\
		ft_err_printf.c\
		err_if_something1.c err_if_something2.c\
		ft_err_put_something1.c ft_err_put_something2.c
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
