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
	char			*direction;
	int				x;
	int				y;
}					t_pos;

typedef struct s_rgb
{
	int				ceiling;
	int				floor;
	int				cR;
	int				cG;
	int				cB;
	int				fR;
	int				fG;
	int				fB;
}					t_rgb;

typedef struct s_xpm
{
	char		*no_key;
	char		*no_value;
	char		*so_key;
	char		*so_value;
	char		*we_key;
	char		*we_value;
	char		*ea_key;
	char		*ea_value;
}				t_xpm;

typedef struct s_data
{
    char			**map;
	// char			*north;
	// char			*west;
	// char			*east;
	// char			*south;
	t_xpm			xpm_json;
	t_pos			player;
	t_rgb			rgb_lst;

}   t_data;

/* validation and map creation */
int		valid_and_parsing(t_data *dbase, char *filename);
void	valid_fd_filename(int fd, char *filename);
// void	valid_filename(char *filename);
char	*initialize_buf(int fd);
void	only_whitespace(char *res);
int valid_whole_file_keep_data(char **lines, t_data *dbase, int i, int count); // if 1 error

// error.c
void	print_error(t_data *data, char *str);
void	clean_data(t_data *data);

// valid_helpers.c
int	is_texture(char *line);
int	is_color(char *line);
int	is_map_line(char *line);
int	check_rgb(char *line);
int check_keep_xpm(t_data *dbase, char *line);



// char	**fd_parse(int fd);
// ******
size_t	ft_startlen(const char *s1, const char *set);
int		ft_check2(char const *set, char const str);
char	*check_newline2(char *join);
char	*ft_strtrim(char const *s1, char const *set);
// size_t	ft_check(char const *set, char const str);
void	check_whitespaces(char **res);
void	check_newline(char *join);
void	check_whitespaces(char **res);
char	*check_newline2(char *join);
int		ft_check2(char const *set, char const str);
size_t	ft_startlen(const char *s1, const char *set);
int		ft_size(int start, int end);
char	*ft_strtrim2(char *s1, char *set);


//error.c


// map validation
char	*cut_front(char *old);
int is_map_valid(char **lines, t_data *dbase);

/* helpers */
// void	print_map(char **map);
void	free_str_array(char **arr);
void	free_res(char *buf, char *res);

// utils
char    **ft_strdup_2d(char **s1, int index);

// checkers
int	check(char s);
int check_disordered_wall(char **map, int j, int i);
int check_side_walls(char **map, int i, int j);
int check_walls(char **map);
int check_chars(char **map);
void clean_map(char **map);
int check_player(char **map);


#endif
