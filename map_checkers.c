/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:32:27 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/05 20:05:35 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//1
int	check(char s)
{
	if (s == ' ' || s == '\t' || s == '\r'
		|| s == '\n' || s == '\v' || s == '\f')
		return (1);
	return (0);
}
//2
int check_side_walls(char **map, int i, int j)
{
	while (map[i])
	{
		j = 0;
		while (map[i][j] && check(map[i][j]) == 1)
			j++;
		if (map[i][j] != '1')
			return (printf("Error\n Wrong map at row %d\n", i), 0);
		i++;
	}
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		j--;
		while (check(map[i][j]) == 1 && j >= 0)
			j--;
		if (map[i][j] != '1')
			return (printf("Error\n Wrong map at row %d\n", i), 0);
		i++;
	}
	return (1);
}

//3
int check_walls(char **map)
{
	int j;
	int i;

	i = 0;
	j = 0;
	while (map[i] && (map[i][j] == '1' || check(map[i][j]) == 1))
		j++;
	if (map[i][j] && map[i][j] != '\0')
		return (printf("Error\nInvalid char or wall missing \
in the first row = %d\n", i), 0);
	while (map[i])
		i++;
	i--;
	j = 0;
	while (map[i] && (map[i][j] == '1' || check(map[i][j]) == 1))
		j++;
	if (map[i][j] != '\0')
		return (printf("Error\nWrong map at row %d\n", i), 0);
	if (check_side_walls(map, 0, 0) == 0)
		return (0);
	else
		return (printf("Error: The side walls are not correctly closed\n"), 0);
	return (1);
}

//4
int check_chars(char **map)
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
	return (1);
}
//5
// inch lav a es funkcian kanchac chi
void clean_map(char **map)
{
	int i;
	
	i = 0;
	while (map[i])
		free(map[i]);
	free(map);
}