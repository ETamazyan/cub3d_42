/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:33:42 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/02 20:37:42 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_loop1(t_game *game, t_player *player, t_draw draw)
{
	draw.dx = player->x;
	draw.dy = player->y;
	draw.size = 10;
	draw.color = 0x00FF00;
	draw_square(draw, game);
	draw_map(game);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		start_angle;
	float		step;
	int			i;
	t_draw		draw;

	player = &game->player;
	move_player(player, game);
	clear_image(game);
	if (DEBUG)
		draw_loop1(game, player, draw);
	start_angle = player->angle - M_PI / 6;
	step = (M_PI / 3) / WIDTH;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_angle, i);
		start_angle += step;
		i++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
