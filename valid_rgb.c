/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:09:00 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/12 12:44:07 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	read_value(int *color, char **line)
{
	skip_whitespace(line);
	if (**line < '0' || **line > '9')
		return (printf("Error\nWrong rgb value\n"), 1);
	*color = ft_atoi(*line, 0, 0);
	if (*color == -1)
		return (printf("Error\nWrong rgb value\n"), 1);
	while (**line && **line >= '0' && **line <= '9')
		(*line)++;
	return (0);
}

int	keep_rgb(int *r, int *g, int *b, char *line)
{
	line++;
	if (read_value(r, &line))
		return (1);
	if (expect_comma(&line))
		return (1);
	if (read_value(g, &line))
		return (1);
	if (expect_comma(&line))
		return (1);
	if (read_value(b, &line))
		return (1);
	skip_whitespace(&line);
	if (*line && *line != '\n' && *line != '\0')
		return (printf("Error expected 3 arguments for rgb value\n"), 1);
	return (0);
}

int	check_rgb(int r, int g, int b)
{
	if (!(r >= 0 && r <= 255) || !(g >= 0 && g <= 255) || \
!(b >= 0 && b <= 255))
		return (printf("Error\nAn RGB value is not in the \
correct range.\n"), 1);
	return (0);
}

int	keep_check_rgb(t_data *db, char *l)
{
	while (*l == ' ' || *l == '\t')
		l++;
	if (*l == 'C' && db->rgb_lst.cr < 0 && db->rgb_lst.cb < 0 \
&& db->rgb_lst.cg < 0)
	{
		if (keep_rgb(&db->rgb_lst.cr, &db->rgb_lst.cg, &db->rgb_lst.cb, l) == 1)
			return (1);
		return (check_rgb(db->rgb_lst.cr, db->rgb_lst.cg, db->rgb_lst.cb));
	}
	else if (*l == 'F' && db->rgb_lst.fr < 0 && db->rgb_lst.fb < 0 \
&& db->rgb_lst.fg < 0)
	{
		if (keep_rgb(&db->rgb_lst.fr, &db->rgb_lst.fg, &db->rgb_lst.fb, l) == 1)
			return (1);
		return (check_rgb(db->rgb_lst.fr, db->rgb_lst.fg, db->rgb_lst.fb));
	}
	else
		return (1);
	return (0);
}
