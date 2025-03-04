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

typedef struct s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct s_data
{
    char			**map;
	char			*north;
	char			*west;
	char			*east;
	char			*south;
    t_pos           player;
}   t_data;

void print_error(t_data *data, char *str);
void is_fd_valid(t_data *data, char *path);
void clean_data(t_data *data);

//lib_utils
int ft_strlen(const char *str);
int	ft_strncmp(const char *s1, const char *s2, int limit);



#endif