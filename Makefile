CC = cc

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

SRCS =  main.c validation.c \
		error.c lib_utils.c \
		parsing.c

INCS = cub3D.h ./get_next_line/get_next_line.h

NAME = cub3D

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) Makefile cub3D.h
		$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

re: fclean all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

.PHONY: all re clean fclean