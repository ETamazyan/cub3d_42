/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:50:10 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/07 21:44:54 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_drawline2(t_line line, t_draw *draw)
{
	if (line.x0 < line.x1)
		draw->n = 1;
	else
		draw->n = -1;
	if (line.y0 < line.y1)
		draw->size = 1;
	else
		draw->size = -1;
}

void	draw_line2d(t_line line, t_game *game)
{
	int		err;
	int		e2;
	t_draw	draw;

	draw.dx = abs(line.x1 - line.x0);
	draw.dy = -abs(line.y1 - line.y0);
	err = draw.dx + draw.dy;
	init_drawline2(line, &draw);
	while (1)
	{
		put_pixel(line.x0, line.y0, line.color, game);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		e2 = 2 * err;
		if (e2 >= draw.dy)
		{
			err += draw.dy;
			line.x0 += draw.n;
		}
		if (e2 <= draw.dx)
		{
			err += draw.dx;
			line.y0 += draw.size;
		}
	}
}
