/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <el.tamazyan03@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:51:01 by etamazya          #+#    #+#             */
/*   Updated: 2025/03/04 21:51:42 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void clean_data(t_data *data)
{
    if (data)
    { 
        data->map = NULL;
        free(*(data)->map);
	    free(data->north);
	    free(data->west);
	    free(data->east);
	    free(data->south);
	    // free(data->player);
    }
}

void print_error(t_data *data, char *str)
{
    write(1, str, ft_strlen(str));
    clean_data(data);
    exit(1);
}