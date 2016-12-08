# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/04 13:11:01 by shamdani          #+#    #+#              #
#    Updated: 2016/12/05 15:36:24 by shamdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = vector.a

FUNC =	new_v.c \
		vadd.c \
		vmult.c \
		vpscal.c \
		vsub.c \
		vnorm.c \
		vhit.c \
		vmult_dbl.c

SRC = $(addprefix ./srcs/, $(FUNC))

OBJ = $(FUNC:.c=.o)

all: $(NAME)

$(NAME):
	@echo "vector lib"
	@clang -Wall -Werror -Wextra -c $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@make clean
	@echo "success!"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all