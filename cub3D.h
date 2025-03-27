/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <el.tamazyan03@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:04:34 by etamazya          #+#    #+#             */
/*   Updated: 2025/03/04 21:00:51 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "./get_next_line/get_next_line.h"
#include "libft/libft.h"


// *****
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <stdio.h>
#include <string.h>
// *****

typedef struct s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct s_dimens
{
	int mi_ban;
} t_dimens;

typedef struct s_data
{
    char			**map;
	char			*north;
	char			*west;
	char			*east;
	char			*south;
	char			*F_color;
	char			*C_color;
    t_pos			player;
}   t_data;


void	print_error(t_data *data, char *str);
void	clean_data(t_data *data);
char	**fd_parse(int fd);

// ******
size_t	ft_startlen(const char *s1, const char *set);
int		ft_check2(char const *set, char const str);
char	*check_newline2(char *join);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_check(char const *set, char const str);
void	check_whitespaces(char **res);
void	check_newline(char *join);
void	check_whitespaces(char **res);
char	*check_newline2(char *join);
int		ft_check2(char const *set, char const str);
size_t	ft_startlen(const char *s1, const char *set);
int		ft_size(int start, int end);
char	*ft_strtrim2(char *s1, char *set);

/* validation and map creation */
int		valid(t_data *dbase, char *filename);
void	valid_fd(int fd);
void	valid_filename(char *filename);
char	*initialize_buf(int fd);
void	only_whitespace(char *res);
void	free_res(char *buf, char *res);
int		validate_file(char **map);

// map validation
char	*cut_front(char *old);

/* helpers */
void	print_map(char **map);


#endif
