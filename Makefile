#NAME = cub3d
#INCDIR = include/
#SRC = main.c \
#		get_map.c \
#		get_player.c \
#		event.c \
#		move.c \
#		init_mlx.c \
#		game.c \
#		draw.c \
#		error.c \
#		arg.c \
#		xmalloc.c \
#		mlx_utils.c \
#		libft/get_next_line.c \
#		libft/get_next_line_utils.c
#OBJ = ${SRC:.c=.o}
#CC = cc
#CFLAGS = -Wall -Wextra -Werror
#CFLAGS += -g
#CFLAGS += -fsanitize=address

#MLX			= libmlx.dylib
#MLXFLAG		= -framework OpenGL -framework AppKit
#MINILIB     = minilibx_mms_20200219

#$(MLX) :
#	cd 	"$(PWD)/$(MINILIB)" && make
#	cd 	"$(PWD)/$(MINILIB)" && cp $(MLX) ../$(MLX)

#.c.o:
#	${CC} ${CFLAGS} -Imlx -o $@ -c $< -I ${INCDIR}

#${NAME}: ${OBJ} $(MLX)
#	$(CC) $(OBJ) $(MLX) $(MLXFLAG) -o $(NAME)
#	#${CC} ${CFLAGS} $(OBJ) -L /usr/X11R6/lib -lmlx -lXext -lX11 -framework OpenGL -framework AppKit -o ${NAME}

#all: ${NAME}

#clean:
#	rm -rf ${OBJ}

#fclean: clean
#	rm -rf ${NAME}

#re: fclean ${NAME}

#simple: ${NAME}
#	rm -rf ${OBJ}
#	./cub3d maps/simple.cub

#min: ${NAME}
#	rm -rf ${OBJ}
#	./cub3d maps/minimalist.cub

#.PHONY: all clean fclean re



NAME		= cub3d
#CC			= clang
CC			= cc
#CFLAGS		= -O3 -Wall -Wextra -Werror -I.
CFLAGS		= -O3 -I.#os update...
MLX			= libmlx.dylib
MLXFLAG		= -framework OpenGL -framework AppKit
MINILIB     = minilibx_mms_20200219
#CFLAGS		= -Wall -Wextra -Werror -I./minilib_mms_20200219

INCDIR = include/


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

OBJS 	= $(SRCS:%.c=%.o)
X_OBJS 	= $(X_SRCS:%.c=%.o)

OBJ_FILES = $(OBJS)
X_OBJ_FILES = $(X_OBJS)

all: $(NAME)

.c.o:
	${CC} ${CFLAGS} -o $@ -c $< -I ${INCDIR}

$(MLX) :
	cd 	"$(PWD)/$(MINILIB)" && make
	cd 	"$(PWD)/$(MINILIB)" && cp $(MLX) ../$(MLX)

#	$(CC) -I /usr/local/include $(OBJ_FILES) $(OBJ_M_B) $(MLX) $(MLXFLAG) -o $(NAME)

$(NAME) : $(OBJ_FILES) $(MLX)
	$(CC) $(OBJ_FILES) $(MLX) $(MLXFLAG) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(MINILIB) clean
	rm -f $(NAME)
	rm -f $(XMAS_NAME)

re: fclean all

bonus: all_b

xmas: $(XMAS_NAME)

bonusrun: fclean all_b
	./cub3D map_bonus.cub

kill_mlx:
	rm -f $(MLX)
	cd 	"$(PWD)/$(MINILIB)" && rm -f $(MLX)

.PHONY: all all_b bonus clean fclean re run kill_mlx
