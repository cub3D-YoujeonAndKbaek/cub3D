# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:57:48 by kbaek             #+#    #+#              #
#    Updated: 2022/07/19 22:20:44 by kbaek            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cu3D

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

INCS_DIR	= ./include/
SRCS_DIR	= ./srcs/
LIB_DIR		= ./libft/
MLX_DIR		= ./minilibx_opengl_20191021/

LIB_NAME	= ./lib/lib_k.a
INCS	= -I include
MLX_FLAGS	= -L./mlx -lmlx -framework OpenGL -framework Appkit

SRCS	= main.c \
			ft_parse.c \
			ft_parse_util.c \
			ft_initialization.c \
			ft_map_dup.c \
			ft_start_game.c \
			ft_key_hook.c \
			ft_key_action.c \
			ft_paint.c \
			ft_raycasting.c \
			ft_ray_init.c \
			


ALLSRCS	= $(addprefix $(SRCS_DIR), $(SRCS))
LIBS	= $(addprefix $(LIB_DIR), $(LIB_NAME))
OBJS	= $(ALLSRCS:.c=.o)

all	: $(NAME)

.c.o	:
	$(CC) $(CFLAGS) -I $(INCS_DIR) -o $@ -c $?

# .c.o	:
# 	$(CC) -I $(INCS_DIR) -o $@ -c $?

$(NAME) : $(OBJS)
	make -C $(LIB_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(LIB_DIR) -l_k -I $(INCS_DIR) -L $(MLX_DIR) -lmlx -framework OpenGL -framework Appkit

clean :
	make -C $(LIB_DIR) clean
	make -C $(MLX_DIR) clean
	$(RM) $(OBJS)

fclean : clean
	make -C $(LIB_DIR) fclean
	$(RM) $(NAME)

re : fclean all

.PHONY  :	all clean fclean re bonus