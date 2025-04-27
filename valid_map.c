/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:32:06 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/27 20:05:59 by etamazya         ###   ########.fr       */
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
			if (map[i][j] == 'N' || map[i][j] == 'S' \
				|| map[i][j] == 'E' || map[i][j] == 'W')
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
