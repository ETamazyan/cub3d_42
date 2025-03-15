/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:00:45 by elen_t13          #+#    #+#             */
/*   Updated: 2025/03/13 15:00:48 by elen_t13         ###   ########.fr       */
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
		free(data->south); // just to keep open
	//	 // free(data->player);
	}
}

void print_error(t_data *data, char *str)
{
	write (1, str, ft_strlen(str));
	clean_data(data);
	exit (1);
}