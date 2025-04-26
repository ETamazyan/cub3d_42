/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:04:33 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/26 20:01:56 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//2
int did_not_reached_map(const char *line, int *count, int order)
{
	*count += 1;
	while (*line && order > 6)
	{
		if (*line != '1' && *line != ' ' && *line != '\t')
			return (0); // aysinqn hasel e map-in petq e stop lini
		line++;
	}
	return (1);
}
