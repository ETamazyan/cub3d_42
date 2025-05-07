/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:48:49 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/07 21:44:45 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_temp(t_line *temp, t_game *game, t_minimap *mm)
{
	temp->x0 = mm->offset_x - mm->minimap_width
		+ (game->player.x * MINIMAP_SCALE);
	temp->y0 = mm->offset_y + (game->player.y * MINIMAP_SCALE);
	temp->x1 = temp->x0 + cos(game->player.angle) * PLAYER_SIZE * 4;
	temp->y1 = temp->y0 + sin(game->player.angle) * PLAYER_SIZE * 4;
	temp->color = RAY_COLOR;
}

void	draw_circle(t_draw draw, t_game *game)
{
	int	radius;
	int	x;
	int	y;

	radius = draw.size / 2;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				put_pixel(draw.dx + radius + x,
					draw.dy + radius + y,
					draw.color, game);
			}
			x++;
		}
		y++;
	}
}

void	draw_dot(int thickness, t_line temp, t_game *game)
{
	int	x2;
	int	y2;

	y2 = -thickness / 2;
	while (y2 <= thickness / 2)
	{
		x2 = -thickness / 2;
		while (x2 <= thickness / 2)
		{
			if (x2 * x2 + y2 * y2 <= (thickness / 2) * (thickness / 2))
				put_pixel(temp.x0 + x2, temp.y0 + y2, temp.color, game);
			x2++;
		}
		y2++;
	}
}

void	init_line(t_line temp, t_line *line)
{
	line->x0 = abs(temp.x1 - temp.x0);
	line->y0 = abs(temp.y1 - temp.y0);
	if (temp.x0 < temp.x1)
		line->x1 = 1;
	else
		line->x1 = -1;
	if (temp.y0 < temp.y1)
		line->y1 = 1;
	else
		line->y1 = -1;
	line->color = line->x0 - line->y0;
}

void	draw_thick_line(t_line temp, int thickness, t_game *game)
{
	t_line	line;
	int		e2;

	init_line(temp, &line);
	while (1)
	{
		draw_dot(thickness, temp, game);
		if (temp.x0 == temp.x1 && temp.y0 == temp.y1)
			break ;
		e2 = 2 * line.color;
		if (e2 > -line.y0)
		{
			line.color -= line.y0;
			temp.x0 += line.x1;
		}
		if (e2 < line.x0)
		{
			line.color += line.x0;
			temp.y0 += line.y1;
		}
	}
}
