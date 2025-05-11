/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:43:05 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/11 17:27:21 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	copy_key(t_data *dbase, char *line) // causes 4 byte leak
{
	int		i;
	char	*value;

	i = 0;
	while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != '\v' \
&& line[i] != '\f' && line[i] != '\r'))
		i++;
	value = ft_strdup(line);
	if (!value)
		return ;
	line += i;
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(value, "NO", 2) == 0)
		dbase->xpm_json.no_value = ft_strdup(line);
	else if (ft_strncmp(value, "SO", 2) == 0)
		dbase->xpm_json.so_value = ft_strdup(line);
	else if (ft_strncmp(value, "WE", 2) == 0)
		dbase->xpm_json.we_value = ft_strdup(line);
	else if (ft_strncmp(value, "EA", 2) == 0)
		dbase->xpm_json.ea_value = ft_strdup(line);
	free(value);
	value = NULL;
}

int	check_keep_xpm(t_data *dbase, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len < 4 || ft_strncmp(line + len - 4, ".xpm", 4) != 0)
		return (printf("Error\nTexture path should end with .xpm\n"), 0);
	while (check_sep(*line, "\t\v\f\r "))
		line++;
	if (*line && (*line != ' ' || *line != '\t' || *line != '\v' || \
*line != '\f' || *line != '\r'))
		copy_key(dbase, line);
	return (1);
}

int	check_design_instance(t_data *dbase)
{
	if (!dbase->rgb_lst.cb || !dbase->rgb_lst.cg || !dbase->rgb_lst.cr || \
!dbase->rgb_lst.fb || !dbase->rgb_lst.fg || !dbase->rgb_lst.fr || \
!dbase->xpm_json.ea_value || !dbase->xpm_json.no_value || \
!dbase->xpm_json.so_value || !dbase->xpm_json.we_value)
		return (1);
	return (0);
}

int	valid_whole_file_keep_data(char **lines, t_data *dbase, int count)
{
	while (*lines)
	{
		if (is_map_line(*lines))
			break ;
		else if (is_texture(*lines))
		{
			if (check_keep_xpm(dbase, *lines) == 1)
				count++;
			else
				break ;
		}
		else if (is_color(*lines))
		{
			if (keep_check_rgb(dbase, *lines) == 0)
				count++;
			else
				break ;
		}
		lines++;
	}
	if (check_design_instance(dbase) == 1)
		return (1);
	if (count == 6)
		return (keep_valid_map(lines, dbase));
	return (0);
}

int	valid_and_parsing(t_data *dbase, char *filename)
{
	char		*buf;
	char		*res;
	char		**fd_inf;
	int			fd;

	fd = open(filename, O_RDONLY);
	valid_fd_filename(dbase, fd, filename);
	res = initialize_buf(fd);
	buf = res;
	res = ft_strtrim(res, "\n\t\v\f\r ");
	check_res(dbase, res, buf);
	res = cut_front(res);
	fd_inf = ft_split(res, '\n');
	if (!fd_inf)
	{
		free(res);
		print_err_exit(dbase, "Error\nWhile allocating\n");
	}
	if (valid_whole_file_keep_data(fd_inf, dbase, 0) == 1)
	{
		free(res);
		free_string_array(fd_inf);
		print_err_exit(dbase, "");
	}
	return (free_string_array(fd_inf), free(res), 0);
}
