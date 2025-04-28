/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:32:06 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/28 13:09:35 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	copy_map(t_data *dbase, char **lines, int i, int j)
{
	int	count;

	i = 0;
	while (lines[i])
		i++;
	count = i;
	dbase->map = (char **)malloc(sizeof(char *) * (count + 1));
	if (!dbase->map)
		return; // failed allocation error message
	i = 0;
	while (lines[i])
	{
		dbase->map[j] = ft_strdup(lines[i]);
		if (!dbase->map[j])
		{
			for (int k = 0; k < j; k++)
				free(dbase->map[k]);
			free(dbase->map);
			return;
		}
		j++;
		i++;
	}
	dbase->map[count] = NULL;
}

// ete sxal exit// kap chuni inch e veradardznum// datarkel d_base-y
int keep_valid_map(char **lines, t_data *dbase) // ete 0 error
{
	//  *** bun validacia ***
	if (!check_chars(lines) || !check_walls(lines) || !check_player(lines)\
	 || !check_disordered_wall(lines, 1, 1) || !check_door(lines))
		return (printf("Errror\n"), 1); // change later to exit
	copy_map(dbase, lines, 0, 0);
	return (1);
}