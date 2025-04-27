/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:32:06 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/27 20:02:55 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int check_disordered_wall(char **map, int j, int i)
{
	while (map[i + 1])
	{
		j = 1;
		while (map[i][j + 1])
		{
			if ((j > (int)ft_strlen(map[i + 1]) - 1 \
			|| j > (int)ft_strlen(map[i - 1]) - 1) 
				&& map[i][j] != '1' && check(map[i][j]) == 0)
				return(printf("Error\n Wrong map at row %d, \
column %d, - %d\n", i, j, map[i][j]), 0); 
			if (check(map[i][j]) == 1 || map[i][j] == '1')
				j++;
			else if (map[i][j] != '1' 
					 && check(map[i][j - 1]) == 0 
					 && check(map[i][j + 1]) == 0 
					 && check(map[i + 1][j]) == 0
					 && check(map[i - 1][j]) == 0)
				j++;
			else
				return(printf("Error\n Wrong map at row %d, \
column %d, - %c\n", i, j, map[i][j]), 0); 
		}
		i++;
	}
	return (1);
}

int check_player(char **map)
{
	int count = 0;
	int i = 0;
	int j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (printf("Error\nSomething wrong with player\n"), 0);
	return (1);
}

int check_door(char **map)
{
    int i;
    int j;

	i = 1;
    while (map[i + 1])
    {
        j = 1;
        while (map[i][j + 1])
        {
            if (map[i][j] == 'D'
                && !(map[i][j - 1] == '1' && map[i][j + 1] == '1')
                && !(map[i - 1][j] == '1' && map[i + 1][j] == '1'))
            {
                printf("Door has wrong position at row %d, column %d\n", i, j);
                return (0);
            }
            j++;
        }
        i++;
    }
	return (1);
}

// ete sxal exit// kap chuni inch e veradardznum// datarkel d_base-y
int is_map_valid(char **lines, t_data *dbase) // ete 0 error
{
	for (int i = 0; lines[i]; i++)
	printf("clone[i] = %s.\n", lines[i]);
	//  *** bun validacia ***
	if (!check_chars(lines) || !check_walls(lines) || !check_player(lines)\
	 || !check_disordered_wall(lines, 1, 1) || !check_door(lines))
		return (printf("Errror\n"), 1); // change later to exit
	(void)dbase;
	return (1);
}

// **************************
// **************************
// ********just keep*********
// **************************
// **************************


// char **copy_lines(char **lines)
// {
// 	char **clone;
// 	int count;
// 	int i;
// 	int j;
	
// 	i = 0;
// 	j = i;
// 	count = 0;
// 	clone = (char **)malloc(sizeof(char *) * (count + 1));
// 	if (!clone)
// 		return NULL;
// 	while (i < count)
// 	{
// 		clone[i] = strdup(lines[i]);
// 		if (!clone[i]) 
// 		{
// 			while (j < i)
// 			{
// 				free(clone[j]);
// 				j++;	
// 			}
// 			free(clone);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	clone[count] = NULL;
// 	return (clone);
// }

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