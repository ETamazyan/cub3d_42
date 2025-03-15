CC = cc

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)  # macOS
    MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
else  # Linux or other systems
    MLX_FLAGS = -lmlx -lX11 -lGL -lGLU
endif

# MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

SRCS =  main.c validation.c \
		error.c \
		parsing.c \
		./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

INCS = cub3D.h

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
