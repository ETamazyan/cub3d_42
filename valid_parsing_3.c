/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:04:33 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/26 21:31:47 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 1 // 3-rd
char	*initialize_buf(int fd)
{
	char		*temp;
	char		*buf;
	char		*res;

	res = ft_strdup("");
	buf = get_next_line(fd);
	while (buf)
	{
		temp = res;
		res = ft_strjoin(res, buf);
		free(temp);
		free(buf);
		buf = get_next_line(fd);
	}
	if (!res)
		exit (1);
	return (res);
}
//2
void	valid_fd_filename(int fd, char *filename)
{
	size_t	len;
	
	len = ft_strlen(filename) - 4;
	if (fd == -1)
	{
		printf("%s", "Error: Invalid filename!\n");
		exit (1);
	}
	if (ft_strncmp(filename + len, ".cub", 4))
	{
		printf("%s", "Error: Invalid file format!\n");
		exit(1);
	}
}

//3
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
//4
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
//5
char	*check_newline2(char *join)
{
	char	*temp;

	temp = join;
	join = ft_strtrim2(join, " \t\n\v\f\r");
	free(temp);
	return (join);
}
