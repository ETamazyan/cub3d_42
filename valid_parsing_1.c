/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:43:05 by maavalya          #+#    #+#             */
/*   Updated: 2025/04/26 13:53:33 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

// 4
// Function to check the order of the identifiers
int check_identifier_order(const char *line, int *exp_ord, int *first_f_c)
{
	printf("line = %s\n", line);
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


/*checking fd, and filename validity*/
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
	// check_dub_nl(res);
	map = ft_split(res, '\n');
	free_res(buf, res);
	if (validate_file(map, 0, 0) == 1)
		return (1);
		/*
		// separate_elements(dbase, map);
		// map_dim = valid_map(map);
		// filling(map_dim, map);
		*/
	(void)map;
	(void)fd;
	(void)dbase;
	return (0);
}
