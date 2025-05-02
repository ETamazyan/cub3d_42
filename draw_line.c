/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:18:25 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/02 20:48:20 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line1(t_player *player, t_game *game, t_rays *rays, int i)
{
	t_coords	coords;
	int			y;
	int			tex_y;
	int			color;

	coords.dist = fixed_dist(player, rays, game);
	coords.height = (BLOCK / coords.dist) * (WIDTH / 2);
	coords.start_y = (HEIGHT - coords.height) / 2;
	coords.end_y = coords.start_y + coords.height;
	if (fabsf(fmodf(rays->ray_x, BLOCK)) < fabsf(fmodf(rays->ray_y, BLOCK)))
		coords.tex_x = (int)fmodf(rays->ray_x, BLOCK);
	else
		coords.tex_x = (int)fmodf(rays->ray_y, BLOCK);
	y = coords.start_y;
	while (y < coords.end_y)
	{
		tex_y = (y - coords.start_y) * game->wall_texture.height
			/ (coords.end_y - coords.start_y);
		color = game->wall_texture.data[tex_y * game->wall_texture.width
			+ coords.tex_x];
		put_pixel(i, y, color, game);
		y++;
	}
}

void	draw_line(t_player *player, t_game *game, float angle, int i)
{
	t_rays	rays;

	rays.ray_x = player->x;
	rays.ray_y = player->y;
	rays.cos_a = cos(angle);
	rays.sin_a = sin(angle);
	while (!touch(rays.ray_x, rays.ray_y, game))
	{
		if (DEBUG)
			put_pixel(rays.ray_x, rays.ray_y, 0x57e422, game);
		rays.ray_x += rays.cos_a;
		rays.ray_y += rays.sin_a;
	}
	if (!DEBUG)
		draw_line1(player, game, &rays, i);
}
