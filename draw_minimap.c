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

#include "cub3D.h"
#define MINIMAP_SCALE 0.2
#define MINIMAP_TILE (BLOCK * MINIMAP_SCALE)

void	draw_line2d(int x0, int y0, int x1, int y1, int color, t_game *game)
{
	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy; // error value e_xy

	while (1)
	{
		put_pixel(x0, y0, color, game);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}


// #define MINIMAP_MAX_WIDTH  (WIDTH / 3)   // Max 1/3 of screen width
// #define MINIMAP_MAX_HEIGHT (HEIGHT / 3)  // Max 1/3 of screen height

// void	draw_minimap(t_game *game)
// {
// 	t_draw	draw;
// 	int		x, y;
// 	int		map_rows = 0;
// 	int		map_cols = 0;

// 	// Get map dimensions
// 	while (game->map[map_rows])
// 	{
// 		int len = strlen(game->map[map_rows]);
// 		if (len > map_cols)
// 			map_cols = len;
// 		map_rows++;
// 	}

// 	// Calculate max tile size to fit within the defined bounds
// 	float tile_w = (float)MINIMAP_MAX_WIDTH / map_cols;
// 	float tile_h = (float)MINIMAP_MAX_HEIGHT / map_rows;
// 	float tile_size = fmin(tile_w, tile_h);
	
// 	int offset_x = WIDTH - (int)(map_cols * tile_size) - 20;
// 	int offset_y = 20;

// 	// Draw map tiles
// 	for (y = 0; y < map_rows; y++)
// 	{
// 		for (x = 0; x < (int)strlen(game->map[y]); x++)
// 		{
// 			if (game->map[y][x] == ' ')
// 				continue;

// 			draw.dx = offset_x + x * tile_size;
// 			draw.dy = offset_y + y * tile_size;
// 			draw.size = tile_size;

// 			if (game->map[y][x] == '1')
// 				draw.color = 0x228B22;
// 			else
// 				draw.color = 0x000000;

// 			draw_square(draw, game);
// 		}
// 	}

// 	// Draw player
// 	draw.size = 4;
// 	draw.color = 0xFF0000;
// 	draw.dx = offset_x + (game->player.x / BLOCK) * tile_size - draw.size / 2;
// 	draw.dy = offset_y + (game->player.y / BLOCK) * tile_size - draw.size / 2;
// 	draw_square(draw, game);

// 	// Direction line
// 	int		line_len = 10;
// 	float	dir_x = cos(game->player.angle);
// 	float	dir_y = sin(game->player.angle);
// 	int		x1 = offset_x + (game->player.x / BLOCK) * tile_size;
// 	int		y1 = offset_y + (game->player.y / BLOCK) * tile_size;
// 	int		x2 = x1 + dir_x * line_len;
// 	int		y2 = y1 + dir_y * line_len;
// 	draw_line2d(x1, y1, x2, y2, 0xFF0000, game);
// }
