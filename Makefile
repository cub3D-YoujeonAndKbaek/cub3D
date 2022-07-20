# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:57:48 by kbaek             #+#    #+#              #
#    Updated: 2022/07/20 17:15:51 by youjeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

INCS_DIR			= ./include/
SRCS_DIR			= ./srcs/
SRCS_BONUS_DIR		= ./srcs_bonus/
LIB_DIR				= ./libft/
MLX_DIR				= ./minilibx_opengl_20191021/

LIB_NAME	= ./lib/lib_k.a
INCS		= -I include
MLX_FLAGS	= -L./mlx -lmlx -framework OpenGL -framework Appkit

SRCS		= main.c \
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

SRCS_BONUS	= main_bonus.c \
			ft_parse_bonus.c \
			ft_parse_util_bonus.c \
			ft_initialization_bonus.c \
			ft_map_dup_bonus.c \
			ft_start_game_bonus.c \
			ft_key_hook_bonus.c \
			ft_key_action_bonus.c \
			ft_paint_bonus.c \
			ft_raycasting_bonus.c \
			ft_ray_init_bonus.c \

ALLSRCS	= $(addprefix $(SRCS_DIR), $(SRCS))
ALLSRCS_BONUS	= $(addprefix $(SRCS_BONUS_DIR), $(SRCS_BONUS))
OBJS	= $(ALLSRCS:.c=.o)
OBJS_BONUS	= $(ALLSRCS_BONUS:.c=.o)


all	: $(NAME)

.c.o	:
	$(CC) $(CFLAGS) -I $(INCS_DIR) -o $@ -c $?

$(NAME) : $(OBJS)
	make -C $(LIB_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(LIB_DIR) -l_k -I $(INCS_DIR) -L $(MLX_DIR) -lmlx -framework OpenGL -framework Appkit

clean :
	make -C $(LIB_DIR) fclean
	make -C $(MLX_DIR) clean
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean : clean
	make -C $(LIB_DIR) fclean
	$(RM) $(NAME)

bonus : $(OBJS_BONUS)
	make -C $(LIB_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_BONUS) -L $(LIB_DIR) -l_k -I $(INCS_DIR) -L $(MLX_DIR) -lmlx -framework OpenGL -framework Appkit

re : fclean all

.PHONY  :	all clean fclean re bonus