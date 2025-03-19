CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./minilibx-linux

LIB_UTILS_DIR = ./libft

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lGL -lGLU

LIB_UTILS_FLAGS = -L$(LIB_UTILS_DIR) -lft

SRCS = main.c validation.c error.c parsing.c \
       ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

INCS = cub3D.h

NAME = cub3D

OBJS = $(SRCS:.c=.o)

all: lib_utils $(NAME)

lib_utils:
	$(MAKE) -C $(LIB_UTILS_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_UTILS_FLAGS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIB_UTILS_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_UTILS_DIR) fclean

.PHONY: all re clean fclean libft