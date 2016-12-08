# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/04 13:11:01 by shamdani          #+#    #+#              #
#    Updated: 2016/12/05 18:34:40 by shamdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = rtv1

FUNC =	rtv1.c \
		parse.c \
		event_key.c \
		raytrace.c \
		error.c \
		put_pixel.c \
		inter_object.c \
		angle_object.c \
		add_obj.c \
		add_env.c \
		solv_quad.c

SRC = $(addprefix ./srcs/, $(FUNC))

OBJ =	$(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -I./

#LFLAGS = -L/usr/X11/lib -lmlx -lXext -lX11
LFLAGS = -lmlx -framework OpenGL -framework AppKit

VECTOR = vector/vector.a
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C vector/
	@make -C libft/
	@clang $(CFLAGS) $(LFLAGS) $(OBJ) $(VECTOR) $(LIBFT) -o $(NAME)


clean:
	@rm -f $(OBJ)
	@make -C ./libft/ clean
	@make -C ./vector/ clean

fclean: clean
	@make -C ./libft/ fclean
	@make -C ./vector/ fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all build clean fclean re v rego