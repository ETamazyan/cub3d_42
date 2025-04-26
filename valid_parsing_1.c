/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:43:05 by maavalya          #+#    #+#             */
/*   Updated: 2025/04/26 19:34:33 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

// 4
// Function to check the order of the identifiers
int check_identifier_order(const char *line, int *exp_ord, int *first_f_c)
{
	printf("check_identifier_order: line = %s\n", line);
	int i = 0;
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 12) || line[i] == '\n')
		i++;
	if (*first_f_c == 0 || *first_f_c == 1)
	{
		if (ft_strncmp(line, "F ", 2) == 0)
		{
			*first_f_c += 1;
			return (0);
		}
		if (ft_strncmp(line, "C ", 2) == 0)
		{
			*first_f_c += 1;
			return (0);
		}
	}
	if (*exp_ord == 0 && ft_strncmp(line, "NO ", 3) == 0)
	{
		*exp_ord = 1;
		return (0);
	}
	if (*exp_ord == 1 && ft_strncmp(line, "SO ", 3) == 0)
	{
		*exp_ord = 2;
		return (0);
	}
	if (*exp_ord == 2 && ft_strncmp(line, "WE ", 3) == 0)
	{
		*exp_ord = 3;
		return (0);
	}
	if (*exp_ord == 3 && ft_strncmp(line, "EA ", 3) == 0)
	{
		*exp_ord = 4;
		return (0);
	}
	if (*first_f_c >= 1 && *exp_ord == 4 && ft_strncmp(line, "F ", 2) == 0)
	{
		*exp_ord = 5;
		return (0);
	}
	if (*first_f_c >= 1 && *exp_ord == 5 && ft_strncmp(line, "C ", 2) == 0)
	{
		*exp_ord = 6;
		return (0);
	}
	return (1);
}






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






// ****************************************
// ****************************************
// ****************************************

void	free_str_array(char **arr)
{
	int	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}


int	is_texture(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (!strncmp(line, "NO", 2) || !strncmp(line, "SO", 2)
		|| !strncmp(line, "WE", 2) || !strncmp(line, "EA", 2));
}

int	is_color(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == 'F' || *line == 'C');
}

int	is_map_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == '1' || *line == '0' || *line == '\t');
}

int	check_rgb(char *line)
{
	int		r, g, b;
	char	*tmp;

	line += 1;
	while (*line == ' ')
		line++;
	r = ft_atoi(line);
	tmp = ft_strchr(line, ',');
	if (!tmp)
		return (0);
	g = ft_atoi(tmp + 1);
	tmp = ft_strchr(tmp + 1, ',');
	if (!tmp)
		return (0);
	b = ft_atoi(tmp + 1);
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}


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
		// printf("aaaa\n");
        if (is_texture(lines[i])) {
			if (check_xpm(lines[i]))
				count++;
			// printf("bbbbbbb\n");
        }
        else if (is_color(lines[i])) {
			if (check_rgb(lines[i]))
			count++;
			// printf("cccc\n");
        }
		// printf("verj\n");
        i++;
    }
    if (count == 6)
        return 1;
		// printf("hasaaaav\n");
    return 0;
}

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
	if (!res)
	{
		free_res(buf, res);
		exit(1);
	}
	res = cut_front(res);
	map = ft_split(res, '\n');
	free_res(buf, res);
	// if not 1 error
	if (!validate_identifiers(map, dbase))
	{
		free_str_array(map);
		write(2, "Error\nInvalid map or config.\n", 30);
		exit(1);
	}
	return (0);
}
