/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:43:05 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/05 15:10:53 by etamazya         ###   ########.fr       */
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
		dbase->xpm_json.no_value = ft_strdup(line);		
	else if (ft_strncmp(value, "SO", 2) == 0)
		dbase->xpm_json.so_value = ft_strdup(line);	
	else if (ft_strncmp(value, "WE", 2) == 0)
		dbase->xpm_json.we_value = ft_strdup(line);	
	else if (ft_strncmp(value, "EA", 2) == 0)
		dbase->xpm_json.ea_value = ft_strdup(line);	
	printf("cpy key = textures: %s,\t%s,\t%s,\t%s\t\n", dbase->xpm_json.no_value, dbase->xpm_json.so_value,dbase->xpm_json.we_value,dbase->xpm_json.ea_value);
	// free(value);
	// value = NULL;
}
// 1
int	check_keep_xpm(t_data *dbase, char *line)
{
	printf("mtav keep xpm\n");
	size_t len;
	
	len = ft_strlen(line);
	if (len < 4 || strcmp(line + len - 4, ".xpm") != 0) //change laterrr strcmp
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line && (*line != ' ' || *line != ' '))
		copy_key(dbase, line);
	return (1);
}

// 2 // 8-rd
// ays funkcian patasxanatu e nayev tvyalnery pahelu hamar
// if 1 error
int valid_whole_file_keep_data(char **lines, t_data *dbase, int count) 
{
	printf("valid_whole_file\n");
	while (*lines)
	{
		if (is_map_line(*lines))
			break ;
		else if (is_texture(*lines))
		{
			printf("aaaaaaaaaaaaaaaaaaaaaaa = %s\n", *lines);
			if (check_keep_xpm(dbase, *lines))
				count++;
			else
				return (0); //should be error
		}
		else if (is_color(*lines))
		{
			printf("bbbbbbbbbbbbbbbbbbbbbbbb = %s\n", *lines);
			if (keep_check_rgb(dbase, *lines))
				count++;
			else
				return (0); // should be error
		}
		lines++;
	}
	printf("textures: %s\t,%s\t,%s\t,%s\t\n", dbase->xpm_json.no_value, dbase->xpm_json.so_value,dbase->xpm_json.we_value,dbase->xpm_json.ea_value);
	
	// printf("rgb_c = %d,%d,%d\n", dbase->rgb_lst.cB, dbase->rgb_lst.cR, dbase->rgb_lst.cG);
 	// printf("rgb_f = %d,%d,%d\n", dbase->rgb_lst.fB, dbase->rgb_lst.fR, dbase->rgb_lst.fG);	
	// printf("sssssssssssssssssssssssssssssssssssssssssssss\n");
	if (count == 6)
		return (keep_valid_map(lines, dbase)); // return (1);
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
	char		**fd_inf;
	int			fd;

	fd = open(filename, O_RDONLY);
	valid_fd_filename(fd, filename);
	res = initialize_buf(fd);
	buf = res;
	only_whitespace(res);
	res = ft_strtrim(res, "\n\t\v\f\r ");
	check_res(res, buf); // changed here, // i think exit may cause leaks
	res = cut_front(res);
	fd_inf = ft_split(res, '\n');
	// if (!fd_inf || !*fd_inf)
	// 	exit(1);
	printf("**********SPLIT*********\n");
	for(int i = 0; fd_inf[i]; i++)
		printf("split fd_inf[i] = %s\n", fd_inf[i]);
	printf("********END_SPLIT********\n");
	free_res(buf, res);
	if (!valid_whole_file_keep_data(fd_inf, dbase, 0)) 	// if not 1 error
	{
		free_str_array(fd_inf);
		write(2, "Error\nInvalid map or config.\n", 30);
		exit(1);
	}
	// printf("bbbbb key = %s, val = %s\n", dbase->xpm_json.ea_key, dbase->xpm_json.ea_value);
	// printf("map_line = %s\n", *map);
	return (0);
}
