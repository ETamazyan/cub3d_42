/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:43:05 by maavalya          #+#    #+#             */
/*   Updated: 2025/04/27 19:56:34 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 1
int check_xpm(char *line)
{
	int fd;
	size_t len;

	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	len = ft_strlen(line);
	if (len < 4 || strcmp(line + len - 4, ".xpm") != 0) // change laterrrr strcmp
		return 0;
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (1); // qani vor menq der chunenq valid xpm, still should be 1
	close(fd);
	return (1);
	}

// 2 // 8-rd
int validate_whole_file(char **lines, t_data *dbase) // if 1 error
{
	int i;
	int count;

	(void)dbase;
	i = 0;
	count = 0;
	while (*lines)
	{
		if (is_map_line(*lines))
			break;
		if (is_texture(*lines)) {
			if (check_xpm(*lines))
				count++;
		}
		else if (is_color(*lines)) {
			if (check_rgb(*lines))
			count++;
		}
		lines++;
	}
	if (count == 6)
		return (is_map_valid(lines, dbase));
	return (0);
}

// 5
static int check_res(char *string, char *buf)
{
	if (!string)
	{
		free_res(buf, string); // achqis ashxatum a menak res-i hamar check later,
		// bervel e valid_and_parsing funckciayic
		exit(1);
	}
	return (0);
}


// 4
int	valid_and_parsing(t_data *dbase, char *filename)
{
	char		*buf;
	char		*res;
	char		**map;
	int			fd;

	fd = open(filename, O_RDONLY);
	valid_fd_filename(fd, filename);
	res = initialize_buf(fd);
	buf = res;
	only_whitespace(res);
	res = ft_strtrim(res, "\n\t\v\f\r ");
	check_res(res, buf); // changed here, // i think exit may cause leaks
	res = cut_front(res);
	map = ft_split(res, '\n');
	free_res(buf, res);
	if (!validate_whole_file(map, dbase)) 	// if not 1 error
	{
		free_str_array(map);
		write(2, "Error\nInvalid map or config.\n", 30);
		exit(1);
	}
	printf("map_line = %s\n", *map);
	return (0);
}
