/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:09:00 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/11 20:45:42 by elen_t13         ###   ########.fr       */
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
	return (1);
}

int	check_rgb(int r, int g, int b)
{
	if (!(r >= 0 && r <= 255) || !(g >= 0 && g <= 255) || \
!(b >= 0 && b <= 255))
		return (printf("Error\nAn RGB value is not in the \
correct range.\n"), 1);
	return (0);
}

int	keep_check_rgb(t_data *db, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == 'C')
	{
		if (!keep_rgb(&db->rgb_lst.cr, &db->rgb_lst.cg, &db->rgb_lst.cb, line))
			return (0);
		return (check_rgb(db->rgb_lst.cr, db->rgb_lst.cg, db->rgb_lst.cb));
	}
	else if (*line == 'F')
	{
		if (!keep_rgb(&db->rgb_lst.fr, &db->rgb_lst.fg, &db->rgb_lst.fb, line))
			return (0);
		return (check_rgb(db->rgb_lst.fr, db->rgb_lst.fg, db->rgb_lst.fb));
	}
	else
		return (1);
	return (0);
}
