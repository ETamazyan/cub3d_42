/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:33:42 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/11 18:51:16 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_draw	draw_loop1(t_game *game, t_player *player)
{
	t_draw	draw;

	draw.dx = player->x;
	draw.dy = player->y;
	draw.size = 10;
	draw.color = 0x00FF00;
	draw_square(draw, game);
	draw_map(game);
	return (draw);
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
		draw = draw_loop1(game, player);
	start_angle = check_angle(player->angle - M_PI / 32);
	step = (M_PI / 4) / game->screen_width;
	i = 0;
	while (i < game->screen_width)
	{
		draw_line(player, game, start_angle, i);
		start_angle += step;
		i++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
	(void)draw;
}

float	check_angle(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}
