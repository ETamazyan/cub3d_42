/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:00:45 by elen_t13          #+#    #+#             */
/*   Updated: 2025/04/27 22:36:00 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void clean_data(t_data *data)
{
	if (data)
	{ 
	//	 data->map = NULL;
	//	 free(*(data)->map);
	//	 free(data->north);
	//	 free(data->west);
	//	 free(data->east);
	if (data->xpm_json.no_key)
		free(data->xpm_json.no_key); // just to keep open
	//	 // free(data->player);
	}
}

void print_error(t_data *data, char *str)
{
	write (1, str, ft_strlen(str));
	clean_data(data);
	exit (1);
}