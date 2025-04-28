/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:03:10 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/28 10:23:53 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void clean_data(t_data *data)
{
	if (data->map)
	{
		int i = 0;
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
		data->map = NULL;
	}
	free(data->xpm_json.no_key);
	free(data->xpm_json.no_value);
	free(data->xpm_json.so_key);
	free(data->xpm_json.so_value);
	free(data->xpm_json.we_key);
	free(data->xpm_json.we_value);
	free(data->xpm_json.ea_key);
	free(data->xpm_json.ea_value);
	data->xpm_json.no_key = NULL;
	data->xpm_json.no_value = NULL;
	data->xpm_json.so_key = NULL;
	data->xpm_json.so_value = NULL;
	data->xpm_json.we_key = NULL;
	data->xpm_json.we_value = NULL;
	data->xpm_json.ea_key = NULL;
	data->xpm_json.ea_value = NULL;
	free(data->player.direction);
	data->player.direction = NULL;
	data->player.x = 0;
	data->player.y = 0;
	data->rgb_lst.ceiling = 0;
	data->rgb_lst.floor = 0;
	data->rgb_lst.cR = 0;
	data->rgb_lst.cG = 0;
	data->rgb_lst.cB = 0;
	data->rgb_lst.fR = 0;
	data->rgb_lst.fG = 0;
	data->rgb_lst.fB = 0;
}

void init_dbase(t_data *dbase)
{
	dbase->map = NULL;
	dbase->xpm_json.no_key = NULL;
	dbase->xpm_json.no_value = NULL;
	dbase->xpm_json.so_key = NULL;
	dbase->xpm_json.so_value = NULL;
	dbase->xpm_json.we_key = NULL;
	dbase->xpm_json.we_value = NULL;
	dbase->xpm_json.ea_key = NULL;
	dbase->xpm_json.ea_value = NULL;
	dbase->player.direction = NULL;
	dbase->player.x = 0;
	dbase->player.y = 0;
	dbase->rgb_lst.ceiling = 0;
	dbase->rgb_lst.floor = 0;
	dbase->rgb_lst.cR = 0;
	dbase->rgb_lst.cG = 0;
	dbase->rgb_lst.cB = 0;
	dbase->rgb_lst.fR = 0;
	dbase->rgb_lst.fG = 0;
	dbase->rgb_lst.fB = 0;
}


int main(int argc, char **argv)
{
	t_data	dbase;

	init_dbase(&dbase); 
	if (argc != 2)
		return (printf("Error: Invalid amount of arguments.\n"), 1);
	if (valid_and_parsing(&dbase, argv[1]) == 1)
		return (1);
	return (0);
}
