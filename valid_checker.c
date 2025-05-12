/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:12:24 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/12 12:41:37 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	skip_whitespace(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	return (0);
}

int	expect_comma(char **line)
{
	skip_whitespace(line);
	if (**line != ',')
		return (printf("Error\n Expected comma\n"), 1);
	(*line)++;
	return (0);
}

int	check_disordered_wall(char **map, int j, int i)
{
	while (map[i + 1])
	{
		j = 1;
		while (map[i][j + 1])
		{
			if ((j > (int)ft_strlen(map[i + 1]) - 1 \
|| j > (int)ft_strlen(map[i - 1]) - 1) \
&& map[i][j] != '1' && check(map[i][j]) == 0)
				return (printf("Error\n Incorrect implementation with \
disordered characters at row %d, column %d, - %d\n", i, j, map[i][j]), 0);
			if (check(map[i][j]) == 1 || map[i][j] == '1')
				j++;
			else if (map[i][j] != '1' \
&& check(map[i][j - 1]) == 0 \
&& check(map[i][j + 1]) == 0 \
&& check(map[i + 1][j]) == 0 \
&& check(map[i - 1][j]) == 0)
				j++;
			else
				return (printf("Error\nInvalid map character at row %d, \
column %d (character: %c)\n", i, j, map[i][j]), 0);
		}
		i++;
	}
	return (1);
}

int	check_player(char	**map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
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
		return (printf("Error\nInvalid number of players\n"), 0);
	return (1);
}

int	check_door(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i + 1])
	{
		j = 1;
		while (map[i][j + 1])
		{
			if (map[i][j] == 'D' \
&& !(map[i][j - 1] == '1' && map[i][j + 1] == '1') \
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
