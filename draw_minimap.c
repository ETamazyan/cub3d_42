/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:04:16 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/02 20:13:59 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap1(t_game *game, t_minimap *mm)
{
	int	y;
	int	x;

	mm->scaled_block = BLOCK * MINIMAP_SCALE;
	mm->offset_x = WIDTH - MINIMAP_PADDING;
	mm->offset_y = MINIMAP_PADDING;
	mm->rows = 0;
	mm->cols = 0;
	while (game->map[mm->rows])
	{
		if ((int)strlen(game->map[mm->rows]) > mm->cols)
			mm->cols = strlen(game->map[mm->rows]);
		mm->rows++;
	}
	mm->minimap_width = mm->cols * mm->scaled_block;
	mm->minimap_height = mm->rows * mm->scaled_block;
	y = -1;
	while (++y < mm->minimap_height)
	{
		x = -1;
		while (++x < mm->minimap_width)
			put_pixel(mm->offset_x - mm->minimap_width + x,
				mm->offset_y + y, 0x222222, game);
	}
}

void	draw_minimap2(t_game *game, t_minimap *mm)
{
	int		y;
	int		x;
	t_draw	draw;

	y = -1;
	while (++y < mm->rows)
	{
		x = -1;
		while (++x < (int)strlen(game->map[y]))
		{
			draw.dx = mm->offset_x - mm->minimap_width + (x * mm->scaled_block);
			draw.dy = mm->offset_y + (y * mm->scaled_block);
			draw.size = mm->scaled_block;
			if (game->map[y][x] == '1')
			{
				draw.color = 0xaaaaaa;
				draw_square(draw, game);
			}
			else
			{
				draw.color = 0x444444;
				draw_square(draw, game);
			}
		}
	}
}

void	draw_minimap(t_game *game)
{
	t_minimap	mm;
	t_draw		draw;
	int			px;
	int			py;
	int			i;

	draw_minimap1(game, &mm);
	draw_minimap2(game, &mm);
	px = mm.offset_x - mm.minimap_width + (game->player.x * MINIMAP_SCALE);
	py = mm.offset_y + (game->player.y * MINIMAP_SCALE);
	draw.size = PLAYER_SIZE;
	draw.color = 0xff0000;
	draw.dx = px - PLAYER_SIZE / 2;
	draw.dy = py - PLAYER_SIZE / 2;
	draw_square(draw, game);
	i = 0;
	while (i < 10)
	{
		px = px + cos(game->player.angle) * 10 * (i / 10.0);
		py = py + sin(game->player.angle) * 10 * (i / 10.0);
		put_pixel(px, py, 0xff0000, game);
		i++;
	}
}
