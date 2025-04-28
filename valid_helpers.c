/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:03 by etamazya          #+#    #+#             */
/*   Updated: 2025/04/28 10:16:40 by etamazya         ###   ########.fr       */
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
int	check_rgb(char *line)
{
	int		r;
	int		g;
	int		b;
	char	*tmp;

	line += 1;
	while (*line == ' ')
		line++;
	r = ft_atoi(line);
	tmp = ft_strchr(line, ',');
	if (!tmp)
		return (0);
	g = ft_atoi(tmp + 1);
	tmp = ft_strchr(tmp + 1, ',');
	if (!tmp)
		return (0);
	b = ft_atoi(tmp + 1);
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

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