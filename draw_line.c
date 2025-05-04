/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:18:25 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/03 17:42:17 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line1(t_player *player, t_game *game, t_rays *rays, int i)
{
	t_coords	coords;
	int			y;
	int			tex_y;
	int			color;
	t_texture	*tex;

	coords.dist = fixed_dist(player, rays, game);
	coords.height = (BLOCK / coords.dist) * (WIDTH / 2);
	coords.start_y = (HEIGHT - coords.height) / 2;
	coords.end_y = coords.start_y + coords.height;
	if (fabsf(fmodf(rays->ray_x, BLOCK)) < fabsf(fmodf(rays->ray_y, BLOCK)))
	{
		coords.tex_x = (int)fmodf(rays->ray_x, BLOCK);
		if (rays->ray_y > player->y)
			tex = &game->south;
		else
			tex = &game->north;
	}
	else
	{
		coords.tex_x = (int)fmodf(rays->ray_y, BLOCK);
		if (rays->ray_x > player->x)
			tex = &game->east;
		else
			tex = &game->west;
	}

	y = coords.start_y;
	while (y < coords.end_y)
	{
		tex_y = (y - coords.start_y) * tex->height / (coords.end_y - coords.start_y);
		color = tex->data[tex_y * tex->width + coords.tex_x];
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
			put_pixel(rays.ray_x, rays.ray_y, 0xFFFFFF, game);
		rays.ray_x += rays.cos_a;
		rays.ray_y += rays.sin_a;
	}
	if (!DEBUG)
		draw_line1(player, game, &rays, i);
}
