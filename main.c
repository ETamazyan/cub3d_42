/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:03:10 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/07 17:40:02 by etamazya         ###   ########.fr       */
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
		return (clean_data(&dbase), 1);
	start_anim(&dbase);
	clean_data(&dbase);
	return (0);
}

// int main(int argc, char **argv)
// {
// 	main_a(argc, argv);
// 	system("leaks cub3D");
// }
