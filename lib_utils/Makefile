# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/09 14:01:00 by etamazya          #+#    #+#              #
#    Updated: 2025/03/15 12:32:42 by elen_t13         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_isalpha.c ft_isdigit.c  \
		ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_strlen.c \
		ft_memset.c ft_bzero.c \
		ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c \
		ft_toupper.c ft_tolower.c \
		ft_strchr.c ft_strrchr.c \
		ft_strncmp.c ft_memchr.c \
		ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c \
		ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c \
		ft_split.c ft_itoa.c \
		ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c 

SRCSB = ft_lstnew.c ft_lstadd_front.c \
		ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c

INCS = libft.h

NAME = libft.a

OBJS =  $(SRCS:.c=.o)

OBJSB = $(SRCSB:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	ar -rcs $@ $^

bonus: $(OBJSB)
	ar -rcs $(NAME) $^

%.o: %.c $(INCS) Makefile
	 $(CC) $(CFLAGS) -I $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
