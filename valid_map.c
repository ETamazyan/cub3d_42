/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:32:06 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/04 22:50:01 by elen_t13         ###   ########.fr       */
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
	printf("dbase tvyal = %s,\t%s,\t%s,\t%s\n", dbase->xpm_json.ea_value, dbase->xpm_json.no_value, dbase->xpm_json.so_value, dbase->xpm_json.we_value);
	if (!check_chars(lines) || !check_walls(lines) || !check_player(lines)\
	|| !check_disordered_wall(lines, 1, 1) || !check_door(lines))
	{
		printf("Errror\n");
		exit(1); // correct this later		
	}
	copy_map(dbase, lines, 0, 0);
	printf("mapic heto tvyal = %s,\t%s,\t%s,\t%s\n", dbase->xpm_json.ea_value, dbase->xpm_json.no_value, dbase->xpm_json.so_value, dbase->xpm_json.we_value);
	for (int i = 0; dbase->map[i]; i++)
		printf("map-y = %s\n", dbase->map[i]);
	printf("***********************************\n");
	return (1);
}