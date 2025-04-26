/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:43:05 by maavalya          #+#    #+#             */
/*   Updated: 2025/04/26 20:01:41 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

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
	return (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) 
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)); // change s
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
	int		r;
	int		g;
	int		b;
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
