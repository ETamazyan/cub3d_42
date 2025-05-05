/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:43:05 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/05 16:00:45 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 5
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
	if (ft_strncmp(value, "NO", 2) == 0)
	{
		dbase->xpm_json.no_value = ft_strdup(line);
	}
	else if (ft_strncmp(value, "SO", 2) == 0)
	{
		dbase->xpm_json.so_value = ft_strdup(line);
	}
	else if (ft_strncmp(value, "WE", 2) == 0)
	{
		dbase->xpm_json.we_value = ft_strdup(line);
	}
	else if (ft_strncmp(value, "EA", 2) == 0)
	{
		dbase->xpm_json.ea_value = ft_strdup(line);
	}
	free(value);
	value = NULL;
}
// 1
int	check_keep_xpm(t_data *dbase, char *line)
{
	// int fd;
	size_t len;
	
	len = ft_strlen(line);
	if (len < 4 || ft_strncmp(line + len - 4, ".xpm", 4) != 0)
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line && (*line != ' ' || *line != ' '))
		copy_key(dbase, line);
	return (1);
}

void	check_design_instance(t_data *dbase)
{
	if (!dbase->rgb_lst.cB || !dbase->rgb_lst.cG || !dbase->rgb_lst.cR ||\
		!dbase->rgb_lst.fB || !dbase->rgb_lst.fG || !dbase->rgb_lst.fR ||\
		!dbase->xpm_json.ea_value || !dbase->xpm_json.no_value ||\
		!dbase->xpm_json.so_value || !dbase->xpm_json.we_value)
		print_err_exit(dbase, "Error while allocating rgb or xpm value\n");
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
		if (is_texture(*lines))
		{
			if (check_keep_xpm(dbase, *lines))
				count++;
			else
				return (1);
		}
		else if (is_color(*lines))
		{
			
			if (keep_check_rgb(dbase, *lines))
				count++;
			else
				return (1);
		}
		lines++;
	}
	check_design_instance(dbase); //added
	if (count == 6)
		return (keep_valid_map(lines, dbase));
	(void)i;
	return (0);
}


// 5
static int check_res(char *string, char *buf)
{
	if (!string)
	{
		free_res(buf, string);
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
	return (0);
}
