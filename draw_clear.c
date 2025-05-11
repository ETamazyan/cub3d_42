/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:22:32 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/11 19:41:30 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= game->screen_width || y >= game->screen_height || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * (game->bpp / 8);
	game->data[index + 0] = (color >> 16) & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = color & 0xFF;
}

void	put_pixel_cf(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= game->screen_width || y >= game->screen_height || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * (game->bpp / 8);
	game->data[index + 2] = (color >> 16) & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 0] = color & 0xFF;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->screen_height / 2)
	{
		x = -1;
		while (++x < game->screen_width)
			put_pixel_cf(x, y, ((game->rgb_lst.cr << 16)
					| (game->rgb_lst.cg << 8) | game->rgb_lst.cb), game);
	}
	y = game->screen_height / 2;
	while (y < game->screen_height)
	{
		x = -1;
		while (++x < game->screen_width)
			put_pixel_cf(x, y, ((game->rgb_lst.fr << 16)
					| (game->rgb_lst.fg << 8) | game->rgb_lst.fb), game);
		y++;
	}
}

void	draw_square(t_draw	draw, t_game *game)
{
	int	x;
	int	y;

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

void	draw_map(t_game *game)
{
	int		y;
	int		x;
	t_draw	draw;

	draw.size = BLOCK;
	draw.color = 0x000000;
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
