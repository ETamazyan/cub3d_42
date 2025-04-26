/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:43:05 by maavalya          #+#    #+#             */
/*   Updated: 2025/04/26 20:14:56 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 1
int check_xpm(char *line)
{
    int fd;
    while (*line && *line != ' ')
        line++;
    while (*line == ' ')
        line++;
    size_t len = ft_strlen(line);
    if (len < 4 || strcmp(line + len - 4, ".xpm") != 0) // change laterrrr strcmp
        return 0;
    fd = open(line, O_RDONLY);
    if (fd < 0)
        return 1; // qani vor menq der chunenq valid xpm, still should be 1
    close(fd);
    return (1);
}

// 2
// if 1 error
int validate_identifiers(char **lines, t_data *dbase)
{
    int i;
    int count;

    (void)dbase;
    i = 0;
    count = 0;
    while (lines[i])
    {
		printf("llll = %s\n", lines[i]);
        if (is_map_line(lines[i]))
            break;
        if (is_texture(lines[i])) {
			if (check_xpm(lines[i]))
				count++;
        }
        else if (is_color(lines[i])) {
			if (check_rgb(lines[i]))
			count++;
        }
        i++;
    }
    if (count == 6)
        return (1);
    return (0);
}
// 3
static int check_res(char *string, char *buf)
{
	if (!string)
	{
		free_res(buf, string); // achqis ashxatum a mena res-i hamar check later,
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
	check_res(res, buf);// changed here, // i think exit may cause leaks
	res = cut_front(res);
	map = ft_split(res, '\n');
	free_res(buf, res);
	if (!validate_identifiers(map, dbase)) 	// if not 1 error
	{
		free_str_array(map);
		write(2, "Error\nInvalid map or config.\n", 30);
		exit(1);
	}
	return (0);
}
