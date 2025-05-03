/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:09:00 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/03 11:20:46 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	keep_rgb(int *r, int *g, int *b, char *line)
{
	char	*tmp;
	
	line += 1;
	while (*line == ' ' || *line == '\t')
		line++;
	*r = ft_atoi(line);
	tmp = ft_strchr(line, ',');
	if (!tmp)
		return (printf("Error\nInvalid rgb line at '%s'\n", line), 0);
	*g = ft_atoi(tmp + 1);
	tmp = ft_strchr(tmp + 1, ',');
	if (!tmp)
		return (printf("Error\nInvalid rgb line at '%s'\n", line), 0);
	*b = ft_atoi(tmp + 1);
	while (*line)
		line++;
	line--;
	if (!(*line >= '0' && *line <= '9'))
		return (printf("Error\nInvalid rgb line at '%s'\n", line), 0);
	return (1); // Succeed spot
}

void check_rgb(t_data *dbase, int r, int g, int b)
{
	// printf("RGBBBBB = __%d,__%d,__%d__", r, g, b);
	if (!(r >= 0 && r <= 255) || !(g >= 0 && g <= 255) || \
	!(b >= 0 && b <= 255))
	{
		printf("Error:\nAn RGB value is not in the correct range.\n");
		exit (1);
	}
	(void)dbase;
}

int	keep_check_rgb(t_data *db, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == 'C')
	{
		if(!keep_rgb(&db->rgb_lst.cR, &db->rgb_lst.cG, &db->rgb_lst.cB, line))
			return (0);
		check_rgb(db, db->rgb_lst.cR, db->rgb_lst.cG, db->rgb_lst.cB);
	}
	else if (*line == 'F')
	{
		if (!keep_rgb(&db->rgb_lst.fR, &db->rgb_lst.fG, &db->rgb_lst.fB, line))
			return (0);
		check_rgb(db, db->rgb_lst.fR, db->rgb_lst.fG, db->rgb_lst.fB);
	}
	else
		return (0);
	return (1); // this is success spot
}