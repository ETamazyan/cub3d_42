/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:22:32 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/02 19:38:56 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * (game->bpp / 8);
	game->data[index + 0] = (color >> 16) & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = color & 0xFF;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0x000000, game);
			x++;
		}
		y++;
	}
}

void	draw_square(t_draw	draw, t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < draw.size)
	{
        x = 0;
        while (x < draw.size)
        {
            put_pixel(x + draw.dx, y + draw.dy, draw.color, game);
            x++;
        }
        y++;
    }
}

void    draw_map(t_game *game)
{
    int y;
    int x;
	t_draw draw;
	draw.size = BLOCK;
	draw.color = 0x57e422;
    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == '1')
            {
				draw.dx = x * BLOCK;
				draw.dy = y * BLOCK;
				draw.size = BLOCK;
				draw_square(draw, game);
			}
            x++;
        }
        y++;
    }
}

void draw_minimap(t_game *game)
{
    t_minimap mm;
	t_draw draw;
    int y, x;

    mm.scaled_block = BLOCK * MINIMAP_SCALE;
    mm.offset_x = WIDTH - MINIMAP_PADDING;
    mm.offset_y = MINIMAP_PADDING;
    mm.rows = 0;
    mm.cols = 0;
    while (game->map[mm.rows])
    {
        int len = strlen(game->map[mm.rows]);
        if (len > mm.cols)
            mm.cols = len;
        mm.rows++;
    }
    mm.minimap_width = mm.cols * mm.scaled_block;
    mm.minimap_height = mm.rows * mm.scaled_block;

    y = 0;
    while (y < mm.minimap_height)
    {
        x = 0;
        while (x < mm.minimap_width)
        {
            put_pixel(mm.offset_x - mm.minimap_width + x, mm.offset_y + y, 0x222222, game);
            x++;
        }
        y++;
    }

    y = 0;
    while (y < mm.rows)
    {
        int row_len = strlen(game->map[y]);
        x = 0;
        while (x < row_len)
        {
            draw.dx = mm.offset_x - mm.minimap_width + (x * mm.scaled_block);
            draw.dy = mm.offset_y + (y * mm.scaled_block);
			draw.size = mm.scaled_block;
            if (game->map[y][x] == '1')
            {
				draw.color = 0xaaaaaa;
				draw_square(draw, game);
			}
            else
            {
				draw.color = 0x444444;
				draw_square(draw, game);}
            x++;
        }
        y++;
    }

    int px = mm.offset_x - mm.minimap_width + (game->player.x * MINIMAP_SCALE);
    int py = mm.offset_y + (game->player.y * MINIMAP_SCALE);
	draw.size = PLAYER_SIZE;
	draw.color = 0xff0000;
	draw.dx = px - PLAYER_SIZE / 2;
	draw.dy = py - PLAYER_SIZE / 2;
	draw_square(draw, game);

    float dir_x = cos(game->player.angle) * 10;
    float dir_y = sin(game->player.angle) * 10;
    int i = 0;
    while (i < 10)
    {
        int dx = px + dir_x * (i / 10.0);
        int dy = py + dir_y * (i / 10.0);
        put_pixel(dx, dy, 0xff0000, game);
        i++;
    }
}