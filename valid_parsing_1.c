/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:43:05 by maavalya          #+#    #+#             */
/*   Updated: 2025/04/28 10:16:30 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void copy_key(t_data *dbase, char *line)
{
	int i;
	char *value;

	i = 0;
	while (line[i] && (line[i] != ' ' && line[i] != '\t'))
		i++;
	value = ft_strncpy_malloc(line, i);
	while (*line && (*line != ' ' && *line != '\t'))
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	if (strcmp(value, "NO") == 0)
	{
		dbase->xpm_json.no_key = ft_strdup("NO");
		dbase->xpm_json.no_value = ft_strdup(line);		
	}
	else if (strcmp(value, "SO") == 0)
	{
		dbase->xpm_json.so_key = ft_strdup(value);
		dbase->xpm_json.so_value = ft_strdup(line);	
	}
	else if (strcmp(value, "WE") == 0)
	{
		dbase->xpm_json.we_key = ft_strdup(value);
		dbase->xpm_json.we_value = ft_strdup(line);	
	}
	else if (strcmp(value, "EA") == 0)
	{
		dbase->xpm_json.ea_key = ft_strdup(value);
		dbase->xpm_json.ea_value = ft_strdup(line);	
	}
	value = NULL;
	free(value);
}
// 1
int	check_keep_xpm(t_data *dbase, char *line)
{
	// int fd;
	size_t len;
	
	len = ft_strlen(line);
	if (len < 4 || strcmp(line + len - 4, ".xpm") != 0) //change laterrr strcmp
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line && (*line != ' ' || *line != ' '))
		copy_key(dbase, line);
	printf("liiiine = %s_\n", line);
	return (1);
}

// 2 // 8-rd
// ays funkcian patasxanatu e nayev tvyalnery pahelu hamar
// if 1 error
int valid_whole_file_keep_data(char **lines, t_data *dbase, int i, int count) 
{
	while (*lines)
	{
		if (is_map_line(*lines))
			break ;
		if (is_texture(*lines)) {
			if (check_keep_xpm(dbase, *lines))
				count++;
		}
		else if (is_color(*lines)) 
			if (check_rgb(*lines))
				count++;
		lines++;
	}
	if (count == 6)
		return (is_map_valid(lines, dbase));
	(void)i;
	return (0);
}


// 5
static int check_res(char *string, char *buf)
{
	if (!string)
	{
		free_res(buf, string);//achqis ashxatum a menak res-i hamar check later,
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
	if (!valid_whole_file_keep_data(map, dbase, 0, 0)) 	// if not 1 error
	{
		free_str_array(map);
		write(2, "Error\nInvalid map or config.\n", 30);
		exit(1);
	}
	printf("map_line = %s\n", *map);
	return (0);
}
