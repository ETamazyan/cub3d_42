/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:00:45 by elen_t13          #+#    #+#             */
/*   Updated: 2025/05/05 16:26:57 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void print_err_exit(t_data *data, char *msg)
{
	write (1, msg, ft_strlen(msg));
	clean_data(data);
	exit (1);
}