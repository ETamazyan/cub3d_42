/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:06:43 by etamazya          #+#    #+#             */
/*   Updated: 2025/03/15 12:27:32 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>

char	*get_next_line(int fd);
char	*ft_readfd(int fd, char *buffer);
char	*ft_filtr(char	*buffer);
char	*ft_str_dup(char *s1, int dir);
size_t	ft_str_len(char *src);
char	*str_join(char *s1, char *s2);
int		ft_str_chr(char *s, int c);

#endif
