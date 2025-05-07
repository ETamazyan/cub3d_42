/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:28:29 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/07 19:03:40 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	lines_count(char **map, int index)
{
	int	i;

	i = 0;
	while (map[index + i])
		i++;
	return (i);
}

char	**ft_strdup_2d(char **s1, int index)
{
	char	**map;
	int		i;

	i = 0;
	map = (char **)malloc(sizeof(char *) * (lines_count(s1, index) + 1));
	if (!map)
		return (NULL);
	while (s1[i + index])
	{
		map[i] = ft_strdup(s1[index + i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}
