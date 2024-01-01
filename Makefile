# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 10:54:58 by jfoltan           #+#    #+#              #
#    Updated: 2023/11/18 16:47:25 by jfoltan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRCS_DIR = ./srcs/
LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)
INCLUDES = -I $(LIBFT_DIR) $(MLX_INC)
CFLAGS =  -Wall -Wextra -Werror -g
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm 
SRCS =  $(SRCS_DIR)fdf.c \
		$(SRCS_DIR)utils.c \
		$(SRCS_DIR)pixels.c \
		$(SRCS_DIR)utils_2.c \
		$(SRCS_DIR)utils_3.c

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(NAME): $(SRCS_DIR) $(SRCS) $(LIBFT) $(MLX_LIB)
	cc $(CFLAGS) $(INCLUDES) $(SRCS) $(LDFLAGS) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
