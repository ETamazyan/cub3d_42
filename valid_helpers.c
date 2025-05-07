/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:03 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/07 18:58:18 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_texture(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2));
}

int	is_color(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == 'F' || *line == 'C');
}

int	is_map_line(char *line)
{
	while (check_sep(*line, "\t\v\f\r "))
		line++;
	return (*line == '1' || *line == '0' || *line == '\t');
}
