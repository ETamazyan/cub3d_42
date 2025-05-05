/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:03:10 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/04 23:15:22 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void clean_data(t_data *data)
{
	int	i;
	
	if (data->map)
	{
		i = 0;
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
		data->map = NULL;
	}
	if (data->xpm_json.no_value)
		free(data->xpm_json.no_value);
	if (data->xpm_json.so_value)
		free(data->xpm_json.so_value);
	if (data->xpm_json.we_value)
		free(data->xpm_json.we_value);
	if (data->xpm_json.ea_value)
		free(data->xpm_json.ea_value);
	data->xpm_json.no_value = NULL;
	data->xpm_json.so_value = NULL;
	data->xpm_json.we_value = NULL;
	data->xpm_json.ea_value = NULL;
	if (data->player.direction)
		free(data->player.direction);
	data->player.direction = NULL;
}

void init_dbase(t_data *dbase)
{
	dbase->map = NULL;
	dbase->xpm_json.no_value = NULL;
	dbase->xpm_json.so_value = NULL;
	dbase->xpm_json.we_value = NULL;
	dbase->xpm_json.ea_value = NULL;
	dbase->player.direction = NULL;
	dbase->player.x = -1;
	dbase->player.y = -1;
	dbase->rgb_lst.cR = -1;
	dbase->rgb_lst.cG = -1;
	dbase->rgb_lst.cB = -1;
	dbase->rgb_lst.fR = -1;
	dbase->rgb_lst.fG = -1;
	dbase->rgb_lst.fB = -1;
}


int main(int argc, char **argv)
{
	t_data	dbase;

	init_dbase(&dbase); 
	if (argc != 2)
		return (printf("Error: Invalid amount of arguments.\n"), 1);
	if (valid_and_parsing(&dbase, argv[1]) == 1)
		return (1);
	// printf("No textures: %s\n", dbase.xpm_json.no_value);
	printf("\n\nmainum mapic heto tvyal = %s,\t%s,\t%s,\t%s\n", dbase.xpm_json.ea_value, dbase.xpm_json.no_value, dbase.xpm_json.so_value, dbase.xpm_json.we_value);
	for (int i = 0; dbase.map[i]; i++)
		printf("map-y = %s\n", dbase.map[i]);
	printf("***********************************\n");
	printf("***********************************\n");
	printf("***********************************\n");
	printf("***********************************\n");
	return (0);
 	// start_anim(&dbase);
}
