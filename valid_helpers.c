/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:03 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/03 11:20:25 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 1
int	is_texture(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) 
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)); // change s
}

// 2
int	is_color(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == 'F' || *line == 'C');
}

// 3
int	is_map_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == '1' || *line == '0' || *line == '\t');
}


//4
// haaarc verjum kara lini inch vor ayl character?


//5
char *ft_strncpy_malloc(const char *src, int n)
{
	int i = 0;
	char *dest = (char *)malloc(n + 1);

	i = 0;
	dest = (char *)malloc(n + 1);
	if (!dest)
		return NULL;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}