SRC = ft_strcat.c ft_toupper.c ft_tolower.c ft_strncpy.c ft_strlen.c \
	ft_strequ.c ft_strdup.c ft_strcpy.c ft_putstr.c ft_memdel.c \
	ft_putstr_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putendl.c \
	ft_putendl_fd.c ft_putchar.c ft_putchar_fd.c ft_memset.c \
	ft_isprint.c ft_isdigit.c ft_isalpha.c ft_isalnum.c ft_isascii.c \
	ft_bzero.c ft_strcmp.c ft_atoi.c ft_strnew.c ft_strsub.c \
	ft_strncmp.c ft_strstr.c ft_strdel.c ft_strncat.c ft_memalloc.c \
	ft_memcpy.c ft_memcmp.c ft_memccpy.c ft_strchr.c ft_strrchr.c \
	ft_strnequ.c ft_strclr.c ft_memmove.c ft_memchr.c ft_strnstr.c \
	ft_strlcat.c ft_strjoin.c ft_striter.c ft_striteri.c ft_strmap.c \
	ft_strmapi.c ft_itoa.c ft_strtrim.c ft_isblank.c ft_strsplit.c \
	ft_getnbr.c get_next_line.c ft_atof.c ft_tablen.c

OBJ = $(SRC:.c=.o)

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@clang -c $(SRC) $(FLAGS)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all