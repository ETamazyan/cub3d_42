/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:43:05 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/06 19:25:59 by etamazya         ###   ########.fr       */
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
	if (!value)
		return ;
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
	// printf("ppppp -------%p\n", value);
	// printf("ppp - %p\n", dbase->xpm_json.no_value);
	// printf("ppp - %p\n", dbase->xpm_json.so_value);
	// printf("ppp - %p\n", dbase->xpm_json.we_value);
	// printf("ppp - %p\n", dbase->xpm_json.ea_value);
// 	free(value);
// 	value = NULL;
}
// 1
int	check_keep_xpm(t_data *dbase, char *line)
{
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

// ************************
void	check_design_instance(t_data *dbase)
{
	if (!dbase->rgb_lst.cB || !dbase->rgb_lst.cG || !dbase->rgb_lst.cR ||\
		!dbase->rgb_lst.fB || !dbase->rgb_lst.fG || !dbase->rgb_lst.fR ||\
		!dbase->xpm_json.ea_value || !dbase->xpm_json.no_value ||\
		!dbase->xpm_json.so_value || !dbase->xpm_json.we_value)
		print_err_exit(dbase, "Error\nWhile allocating rgb or xpm value\n");
}


// 2 // 8-rd
// ays funkcian patasxanatu e nayev tvyalnery pahelu hamar
// if 1 error
int valid_whole_file_keep_data(char **lines, t_data *dbase, int count) 
{
	while (*lines)
	{
		if (is_map_line(*lines))
			break ;
		else if (is_texture(*lines)) // change to else if
		{
			if (check_keep_xpm(dbase, *lines)) // add here exit
				count++;
			else
				break ;
		}
		else if (is_color(*lines))
		{
			if (keep_check_rgb(dbase, *lines)) // add here exit
				count++;
			else
				break ;
		}
		lines++;
	}
	check_design_instance(dbase); //added exit
	if (count == 6)
		return (keep_valid_map(lines, dbase)); // add here exit
	return (0);
}


// 5
int check_res(t_data *dbase, char *string, char *buf)
{
	if (!string)
	{
		// free_res(buf, string);
		free(buf);
		print_err_exit(dbase, "Error\nWhile allocating.\n");
	}
	
	return (0);
}


// 4
// int	valid_and_parsing(t_data *dbase, char *filename)
// {
// 	char		*buf;
// 	char		*res;
// 	char		**fd_inf;
// 	int			fd;

// 	fd = open(filename, O_RDONLY);
// 	valid_fd_filename(dbase, fd, filename);
// 	res = initialize_buf(fd);
// 	buf = res;
// 	only_whitespace(dbase, res);
// 	res = ft_strtrim(res, "\n\t\v\f\r ");
// 	check_res(dbase, res, buf); // changed here, // i think exit may cause leaks
// 	res = cut_front(res);
// 	fd_inf = ft_split(res, '\n'); // check split
// 	// printf("%p, %p, %p\n", buf, res, filename);
// 	free_res(buf, res);
// 	if (!fd_inf)
// 		print_err_exit(dbase, "Error\nWhile allocating\n");
// 	// shoud mbe from below
// 	if (valid_whole_file_keep_data(fd_inf, dbase, 0) == 0)
// 	{
// 			close(fd); // check this later
// 			clean_dbl_chr_ptr(fd_inf);
// 			print_err_exit(dbase, ""); // make this to exit itself
// 	}
// 	close(fd); // check this later
// 	return (0);
// }

int valid_and_parsing(t_data *dbase, char *filename)
{
    char *buf = NULL;
    char *res = NULL;
    char **fd_inf = NULL;
    int fd;

    fd = open(filename, O_RDONLY);
    valid_fd_filename(dbase, fd, filename);
    
    buf = initialize_buf(fd);
    if (!buf)
        print_err_exit(dbase, "Error\nMemory allocation failed\n");
    
    only_whitespace(dbase, buf);
    
    res = ft_strtrim(buf, "\n\t\v\f\r ");
    // free(buf); // We're done with original buf
    if (!res)
        print_err_exit(dbase, "Error\nMemory allocation failed\n");
    
    res = cut_front(res);
    fd_inf = ft_split(res, '\n');
    // free(res); // We're done with res after splitting
    if (!fd_inf)
        print_err_exit(dbase, "Error\nWhile allocating\n");
    
    if (valid_whole_file_keep_data(fd_inf, dbase, 0) == 0)
    {
        close(fd);
        clean_dbl_chr_ptr(fd_inf);
        print_err_exit(dbase, "");
    }
    close(fd);
    return (0);
}