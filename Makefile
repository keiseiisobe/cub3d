# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/29 19:25:17 by miyazawa.ka       #+#    #+#              #
#    Updated: 2024/07/16 18:34:02 by miyazawa.ka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

#CC			= clang
CC			= cc
CFLAGS		= -O3 -Wall -Wextra -Werror
#CFLAGS		+= -g
#CFLAGS		+= -fsanitize=address

MLXFLAG		= -framework OpenGL -framework AppKit


MLX			= libmlx.dylib
MINILIB		= minilibx_mms_20200219

FT			= libft.a
FTLIB		= libft/



INCDIR = include/

SRCS = main.c \
		get_map.c \
		get_map2.c \
		get_player.c \
		event.c \
		move.c \
		move2.c \
		init_mlx.c \
		init_texture.c \
		game.c \
		draw.c \
		draw2.c \
		error.c \
		arg.c \
		arg2.c \
		arg3.c \
		arg4.c \
		arg5.c \
		xmalloc.c \
		mlx_utils.c \
		debug.c

OBJS 	= $(SRCS:%.c=%.o)

all: $(NAME)

.c.o:
	${CC} ${CFLAGS} -o $@ -c $< -I ${INCDIR} -I $(FTLIB) -I $(MINILIB)

$(MLX) :
	make -C $(MINILIB)
	cp $(MINILIB)/$(MLX) .

$(FT) :
	make -C $(FTLIB)
	cp $(FTLIB)/$(FT) .

$(NAME) : $(OBJS) $(MLX) $(FT)
	$(CC) $(OBJS) $(MLX) $(FT) $(MLXFLAG) -o $(NAME)

clean:
	$(MAKE) -C $(FTLIB) clean
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C $(FTLIB) fclean
	rm -rf $(FT)
	$(MAKE) -C $(MINILIB) clean
	rm -rf $(MLX)
	rm -rf $(NAME)

re: fclean all

j: all
	./cub3d maps/simple.cub

min: all
	make
	make clean
	./cub3d maps/valid/minimalist.cub

kill_mlx:
	rm -rf $(MLX)
	cd 	"$(PWD)/$(MINILIB)" && rm -f $(MLX)

kill_ft:
	rm -rf $(FT)
	cd 	"$(PWD)/$(FTDIR)" && rm -f $(FT)

.PHONY: all clean fclean re kill_mlx
