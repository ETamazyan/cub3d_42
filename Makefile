CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./minilibx-linux

LIB_UTILS_DIR = ./libft

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lGL -lGLU

LIB_UTILS_FLAGS = -L$(LIB_UTILS_DIR) -lft

SRCS = main.c validation.c error.c parsing.c trim_map.c\
       ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c\
	   utils.c indexing_map.c

INCS = cub3D.h

NAME = cub3D

OBJS_DIR = objects/

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS:.c=.o)

all: lib_utils $(NAME)

lib_utils:
	$(MAKE) -C $(LIB_UTILS_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_UTILS_FLAGS) $(MLX_FLAGS) -o $(NAME)

$(OBJS_DIR)%.o: %.c $(HEADERS) Makefile
		@mkdir -p $(OBJS_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

clean:
	@$(RM) $(OBJS)
	$(MAKE) -C $(LIB_UTILS_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIB_UTILS_DIR) fclean

.PHONY: all re clean fclean libft

# NAME = game
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux
# SRC = src/main.c src/player.c
# OBJ = $(SRC:.c=.o)

# LFLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz

# all: mlx $(NAME)

# mlx:
# 	git clone https://github.com/42Paris/minilibx-linux.git || true
# 	make -C minilibx-linux

# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJ)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all
