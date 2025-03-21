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

void	valid_fd(int fd)
{
	if (fd == -1)
	{
		printf("%s", "Error: Invalid filename!\n");
		exit (1);
	}
}


/*checking fd, and filename validity*/
int	valid(char *filename)
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
	for(int i = 0; map[i]; i++)
	{	for(int j = 0; map[i][j]; j++)
			printf("%c", map[i][j]);
		printf("\n");}
	// separate_elements(map);
	// map_dim = valid_map(map);
	// filling(map_dim, map);
	return (0);
}