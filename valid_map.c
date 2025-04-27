/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:32:06 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/27 18:46:06 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check(char s)
{
	if (s == ' ' || s == '\t' || s == '\r'
		|| s == '\n' || s == '\v' || s == '\f')
		return (1);
	return (0);
}

int check_walls(char **map)
{
	int j;
	int i;

	i = 0;
	j = 0;
	while (map[i] && map[i][j] && map[i][j] != '\n' && (map[i][j] == '1' || check(map[i][j]) == 1))
		j++;
	if (map[i][j] && map[i][j] != '\0')
		return (printf("Wrong map at row %d\n", i), 0);
	while (map[i])
		i++;
	i--;
	j = 0;
	while (map[i] && (map[i][j] == '1' || check(map[i][j]) == 1))
		j++;
	if (map[i][j] != '\0')
		return (printf("Wrong map at row %d\n", i), 0);
	return (1);
}

char **copy_lines(char **lines)
{
	char **clone;
	int count;
	int i;
	int j;
	
	i = 0;
	j = i;
	count = 0;
	clone = (char **)malloc(sizeof(char *) * (count + 1));
	if (!clone)
		return NULL;
	while (i < count)
	{
		clone[i] = strdup(lines[i]);
		if (!clone[i]) 
		{
			while (j < i)
			{
				free(clone[j]);
				j++;	
			}
			free(clone);
			return (NULL);
		}
		i++;
	}
	clone[count] = NULL;
	return (clone);
}

static int check_chars(char **map)
{
	int i = 0;
	int j;
	
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!(map[i][j] == '1' || map[i][j] == '0' ||
				  map[i][j] == 'N' || map[i][j] == 'S' ||
				  map[i][j] == 'W' || map[i][j] == 'E' ||
				  map[i][j] == 'D' || map[i][j] == ' ' ||
				  map[i][j] == '\t' || map[i][j] == '\n'))
				  return (printf("Error\nInvalid character '%c' at line %d, \
column %d\n", map[i][j], i, j), 0);
			j++;
		}
		i++;
	}
	return (1); // Valid
}
void clean_map(char **map)
{
	int i;
	
	i = 0;
	while (map[i])
		free(map[i]);
	free(map);
}

// ete sxal exit// kap chuni inch e veradardznum
int is_map_valid(char **lines, t_data *dbase) // ete 0 error
{
	// char **cl_map;
	
	// cl_map = copy_lines(lines);
	// if (!cl_map)
	// 	return 0;
	for (int i = 0; lines[i]; i++)
	printf("clone[i] = %s.\n", lines[i]);
	//  *** bun validacia ***
	if (!check_chars(lines) || !check_walls(lines))
		return (printf("Errror\n"), 1);
	// *************************
	// chmoranalu hamar togh mna
	// if (cl_map)
	// 	clean_map(cl_map);
	(void)dbase; // vor compile lini
	printf("aaaaaaaaaaaaaaaaaa\n");
	return (1);
	return (0); // error
}

// **************************
// **************************
// ********just keep*********
// **************************
// **************************

// int	check_walls(char **map)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			j++;
// 		}
// 	i++;
// 	}
// 	int		j;

// 	j = 0;
// 	while (map->data[0][j] || map->data[map->raws - 1][j])
// 	{
// 		if (map->data[0][j] != '1'
// 				|| map->data[map->raws - 1][j] != '1')
// 			exit(write(2, "Invalid map\n", 12));
// 		j++;
// 	}
// 	check_sidewalls(map);
// 	(void)map;
// 	return (1);
// }

// void	check_sidewalls(char **map)
// {
// 	int	i;

// 	i = 0;
// 	while (i < map->raws)
// 	{
// 		if (map->data[i][0] != '1'
// 				|| map->data[i][map->cols - 1] != '1')
// 			exit(write(2, "Invalid map\n", 12));
// 		i++;
// 	}
// }