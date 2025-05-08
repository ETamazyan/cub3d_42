CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

MLX_DIR = ./minilibx-linux

LIB_UTILS_DIR = ./libft

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lGL -lGLU

LIB_UTILS_FLAGS = -L$(LIB_UTILS_DIR) -lft

SRCS = main.c valid_parsing_1.c error.c valid_parsing_2.c trim_map.c\
       ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c\
	   utils.c valid_helpers.c valid_parsing_3.c clean.c \
	   valid_checker.c valid_map.c map_checkers.c valid_rgb.c \
	   anim1.c anim2.c draw_clear.c draw_minimap.c draw_line.c draw_loop.c

INCS = cub3D.h

NAME = cub3D

OBJS_DIR = objects/

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS:.c=.o)

all: lib_utils $(NAME)

lib_utils:
	$(MAKE) -C $(LIB_UTILS_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_UTILS_FLAGS) $(MLX_FLAGS) -o $(NAME) -lm

$(OBJS_DIR)%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
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
