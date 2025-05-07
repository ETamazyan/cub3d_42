/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:04:33 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/07 18:23:24 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*initialize_buf(int fd)
{
	char	*temp;
	char	*buf;
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	buf = get_next_line(fd);
	while (buf)
	{
		temp = res;
		res = ft_strjoin(res, buf);
		free(temp);
		free(buf);
		if (!res)
			return (NULL);
		buf = get_next_line(fd);
	}
	return (res);
}

void	valid_fd_filename(t_data *dbase, int fd, char *filename)
{
	size_t	len;

	len = ft_strlen(filename) - 4;
	if (fd == -1)
		print_err_exit(dbase, "Error\nInvalid filename!\n");
	if (ft_strncmp(filename + len, ".cub", 4))
	{
		close(fd);
		print_err_exit(dbase, "Error\nInvalid file format!\n");
	}
}

void	check_newline(char *join)
{
	int	i;

	i = 0;
	while (join[i])
	{
		if (join[i] == '\n' && join[i + 1] == '\n')
		{
			write(2, "Invalid map\n", 12);
			exit(0);
		}
		i++;
	}
}

void	check_whitespaces(char **res)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (res[i])
	{
		temp = res[i];
		res[i] = ft_strtrim(res[i], " \t\n\v\f\r");
		free(temp);
		i++;
	}
}

char	*check_newline2(char *join)
{
	char	*temp;

	temp = join;
	join = ft_strtrim2(join, " \t\n\v\f\r");
	free(temp);
	return (join);
}
