/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:43:05 by maavalya          #+#    #+#             */
/*   Updated: 2025/03/21 06:24:59 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int is_line_valid(const char *line, int *counter)
{
	*counter += 1;
	while (*line)
	{
		if (*line != '1' && *line != ' ' && *line != '\t')
			return 0;
		line++;
	}
	return 1; 
}

static int is_valid_identifier(const char *line) {
    if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 || strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0) {
        const char *path = line + 3;
        if (*path == '\0') {
            printf("Error: Empty path for texture.\n");
            return 0;
        }
        while (*path != '\0') {
            if (!ft_isalnum(*path) && *path != '/' && *path != '.') {
                printf("Error: Invalid character in texture path: %s\n", path);
                return 0;
            }
            path++;
        }
        return 1;
    } else if (strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0) {
        const char *rgb_values = line + 2;
        int r, g, b;
        if (sscanf(rgb_values, "%d,%d,%d", &r, &g, &b) != 3) {
            printf("Error: Invalid RGB values for %s: %s\n", line, rgb_values);
            return 0;
        }
        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
            printf("Error: RGB values out of range for %s: %s\n", line, rgb_values);
            return 0;
        }
        return 1;
    }
    return 0;
}

// Function to check the order of the identifiers
static int check_identifier_order(const char *line, int *expected_order, int *first_f_c)
{
	printf("line = %s\n", line);
	int flag = 0;
    int i = 0;
    while (line[i] == 32 || (line[i] >= 9 && line[i] <= 12) || line[i] == '\n')
        i++;
    if (*first_f_c == 0 || *first_f_c == 1) {
        if (strncmp(line, "F ", 2) == 0)
		{
			*expected_order = 0;
            *first_f_c = 1; // check later
			flag = 1;
            return 0;
        }
        if (strncmp(line, "C ", 2) == 0)
		{
            *expected_order = 0;
            *first_f_c = 2; // check later
			flag = 1;
            return 0;
        }
    }
	if (*expected_order == 0 && strncmp(line, "NO ", 3) == 0) {
		*expected_order = 1;
        return 0;
    }
	if (*expected_order == 1 && strncmp(line, "SO ", 3) == 0) {
        *expected_order = 2;
        return 0;
    }
    if (*expected_order == 2 && strncmp(line, "WE ", 3) == 0) {
        *expected_order = 3;
        return 0;
    }
    if (*expected_order == 3 && strncmp(line, "EA ", 3) == 0) {
        *expected_order = 4;
        return 0;
    }
    if (*first_f_c >= 1 && *expected_order == 4 && strncmp(line, "F ", 2) == 0) {
        *expected_order = 5;
        return 0;
    }
    if (*first_f_c >= 1 && *expected_order == 5 && strncmp(line, "C ", 2) == 0) {
        *expected_order = 6;
        return 0;
    }
(void)flag;
    // If an identifier is encountered out of order, return 1 to indicate error
    return 1;
}

// Function to validate the entire file
static int validate_file(char **map)
{
	int counter = 0;
    int expected_order = 0;
    int first_f_c = 0;
    for (int i = 0; map[i] != NULL; i++) 
	{
        const char *line = map[i];

        if (line[0] == '\n')
            continue;
        if (is_line_valid(line, &counter) && !is_valid_identifier(line))
            return (1);
        if (check_identifier_order(line, &expected_order, &first_f_c) == 1)
            return (printf("Error: Invalid order or unknown identifier: %s\n", line), 1);
    }

    return 0;
}

void	valid_filename(char *filename)
{
	size_t	len;

	len = ft_strlen(filename) - 4;
	if (ft_strncmp(filename + len, ".cub", 4))
	{
		printf("%s", "Error: Invalid file format!\n");
		exit(1);
	}
}

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

void	valid_fd(int fd)
{
	if (fd == -1)
	{
		printf("%s", "Error: Invalid filename!\n");
		exit (1);
	}
}


/*checking fd, and filename validity*/
int	valid(t_data *dbase, char *filename)
{
	char		*buf;
	char		*res;
	char		**map;
	int			fd;
	// t_dimens	map_dim;
	
	fd = open(filename, O_RDONLY);
	valid_fd(fd);
	valid_filename(filename);
	res = initialize_buf(fd);
	buf = res;
	only_whitespace(res);
	res = ft_strtrim(res, "\n\t\v\f\r ");
	if (!res)
	{
		free_res(buf, res);
		exit(1);
	}
	res = cut_front(res);
	// check_dub_nl(res);
	map = ft_split(res, '\n');
	free_res(buf, res);
	// for(int i = 0; map[i]; i++)
	// {	for(int j = 0; map[i][j]; j++)
	// 		printf("%c", map[i][j]);
	// 	printf("\n");}
	if(validate_file(map) == 1)
	return (1);
	// separate_elements(dbase, map);
	// map_dim = valid_map(map);
	// filling(map_dim, map);
	(void)buf;
	(void)res;
	(void)map;
	(void)fd;
	(void)dbase;
	return (0);
}






// *** ADDITIONAL FUNCTIONS ***

// void separate_elements(t_data *dbase, char **map)
// {
		// // char **template = map; // navsyaki, heto i-n ev j-n kareli e poxel pointerov
		// int	i;
		// int j;
		// char *exp_order[] = {"NO", "SO", "WE", "EA", "F", "C"};
		// i = 0;

		// CHANGE THE LOGIC
		// while (map[i])
		// {
		// 	j = 0;
		// 	while (map[i][j])
		// 	{
		// 		while (map[i][j] == 32 || (map[i][j] >= 9 && map[i][j] <= 12))
		// 			j++;
		// 		if (ft_strncmp(&map[i][j], "NO ", 3) == 0) // add later whites spaces as [2] character
		// 			dbase->north = map[i++];
		// 		if (ft_strncmp(&map[i][j], "SO ", 3) == 0) // add later whites spaces as [2] character
		// 			dbase->south = map[i++];
		// 		if (ft_strncmp(&map[i][j], "WE ", 3) == 0) // add later whites spaces as [2] character
		// 			dbase->west = map[i++];
		// 		if (ft_strncmp(&map[i][j], "EA ", 3) == 0) // add later whites spaces as [2] character
		// 			dbase->east = map[i++];
		// 		j++;
		// 	}
		// 	i++;
		// }
// }

// KEEP THIS IN ADVANCE
// void separate_elements(t_data *dbase, char **map)
// {
	// 	// char **template = map; // navsyaki, heto i-n ev j-n kareli e poxel pointerov
	// 	int	i;
	// 	int j;
	//	 // char *expected_order[] = {"NO", "SO", "WE", "EA", "F", "C"};
	// 	i = 0;
	// 	while (map[i])
	// 	{
		// 		j = 0;
		// 		while (map[i][j])
		// 		{
			// 			while (map[i][j] == 32 || (map[i][j] >= 9 && map[i][j] <= 12))
			// 				j++;
			// 			if (ft_strncmp(&map[i][j], "NO ", 3) == 0) // add later whites spaces as [2] character
			// 				dbase->north = map[i++];
// 			if (ft_strncmp(&map[i][j], "SO ", 3) == 0) // add later whites spaces as [2] character
// 				dbase->south = map[i++];
// 			if (ft_strncmp(&map[i][j], "WE ", 3) == 0) // add later whites spaces as [2] character
// 				dbase->west = map[i++];
// 			if (ft_strncmp(&map[i][j], "EA ", 3) == 0) // add later whites spaces as [2] character
// 				dbase->east = map[i++];
// 			j++;
// 		}
// 		i++;
// 	}
// }

// t_dimens	valid_map(char **map)
// {}

//void filling(map_dim, map) 
// {}

// void	check_dub_nl(char	*buf)
// {
// 	int	flag;
// 	int	i;

// 	i = 0;
// 	flag = 0;
// 	while (buf[i])
// 	{
// 		if (buf[i] != '\n')
// 			flag = 0;
// 		if (buf[i] == '\n' && flag == 0)
// 			flag = 1;
// 		else if (buf[i] == '\n' && flag == 1)
// 		{
// 			ft_printf("%s", "Error\nDouble new line!");
// 			free(buf);
// 			exit (1);
// 		}
// 		i++;
// 	}
// }