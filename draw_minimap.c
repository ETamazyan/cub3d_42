/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:39:10 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/07 22:07:02 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap_background(t_game *game, t_minimap *mm)
{
	int	y;
	int	x;

	mm->scaled_block = BLOCK * MINIMAP_SCALE;
	mm->offset_x = game->screen_width - MINIMAP_PADDING;
	mm->offset_y = MINIMAP_PADDING;
	mm->rows = 0;
	mm->cols = 0;
	while (game->map[mm->rows])
	{
		if ((int)ft_strlen(game->map[mm->rows]) > mm->cols)
			mm->cols = (int)ft_strlen(game->map[mm->rows]);
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
				mm->offset_y + y, BACKGROUND_COLOR, game);
	}
}

void	draw_minimap_tiles(t_game *game, t_minimap *mm)
{
	int		y;
	int		x;
	t_draw	draw;

	y = -1;
	while (++y < mm->rows)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map[y]))
		{
			draw.dx = mm->offset_x - mm->minimap_width + (x * mm->scaled_block);
			draw.dy = mm->offset_y + (y * mm->scaled_block);
			draw.size = mm->scaled_block;
			if (game->map[y][x] == '1')
			{
				draw.color = WALL_COLOR;
				draw_square(draw, game);
			}
			else if (ft_strchr("0NSEW", game->map[y][x]))
			{
				draw.color = FLOOR_COLOR;
				draw_square(draw, game);
			}
		}
	}
}

void	draw_player_on_minimap(t_game *game, t_minimap *mm)
{
	t_draw	draw;
	t_line	temp;
	t_line	line;

	temp.x0 = mm->offset_x - mm->minimap_width
		+ (game->player.x * MINIMAP_SCALE);
	temp.y0 = mm->offset_y + (game->player.y * MINIMAP_SCALE);
	draw.size = PLAYER_SIZE;
	draw.color = PLAYER_COLOR;
	draw.dx = temp.x0 - PLAYER_SIZE / 2;
	draw.dy = temp.y0 - PLAYER_SIZE / 2;
	draw_circle(draw, game);
	temp.x1 = temp.x0 + cos(game->player.angle) * PLAYER_SIZE * 2;
	temp.y1 = temp.y0 + sin(game->player.angle) * PLAYER_SIZE * 2;
	line.x0 = temp.x0;
	line.y0 = temp.y0;
	line.x1 = temp.x1;
	line.y1 = temp.y1;
	line.color = PLAYER_COLOR;
	draw_line2d(line, game);
}

void	draw_rays_on_minimap(t_game *game, t_minimap *mm)
{
	t_line	temp;
	int		i;
	float	ray_angle;
	t_line	line;

	init_temp(&temp, game, mm);
	draw_thick_line(temp, 2, game);
	i = -3;
	while (i <= 3)
	{
		ray_angle = game->player.angle + (i * 0.1);
		temp.x1 = temp.x0 + cos(ray_angle) * PLAYER_SIZE * 3;
		temp.y1 = temp.y0 + sin(ray_angle) * PLAYER_SIZE * 3;
		line.x0 = temp.x0;
		line.y0 = temp.y0;
		line.x1 = temp.x1;
		line.y1 = temp.y1;
		line.color = RAY_COLOR;
		draw_line2d(line, game);
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	t_minimap	mm;

	draw_minimap_background(game, &mm);
	draw_minimap_tiles(game, &mm);
	draw_rays_on_minimap(game, &mm);
	draw_player_on_minimap(game, &mm);
}
