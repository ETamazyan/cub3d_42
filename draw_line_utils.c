/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:46:14 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/10 19:51:59 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_texture	*assign_textures1(t_coords *coords, float hit_y_mod,
	t_rays *rays, t_game *game)
{
	t_texture	*tex;

	tex = NULL;
	coords->tex_x = (int)hit_y_mod;
	if (rays->cos_a > 0)
		tex = &game->west;
	else
		tex = &game->east;
	return (tex);
}

t_texture	*assign_textures(t_rays *rays, t_game *game,
	t_texture *tex, t_coords *coords)
{
	float	hit_x_mod;
	float	hit_y_mod;
	float	dist_to_x_boundary;
	float	dist_to_y_boundary;

	hit_x_mod = fmodf(rays->ray_x, BLOCK);
	hit_y_mod = fmodf(rays->ray_y, BLOCK);
	if (hit_x_mod < 0)
		hit_x_mod += BLOCK;
	if (hit_y_mod < 0)
		hit_y_mod += BLOCK;
	dist_to_x_boundary = fminf(hit_x_mod, BLOCK - hit_x_mod);
	dist_to_y_boundary = fminf(hit_y_mod, BLOCK - hit_y_mod);
	if (dist_to_x_boundary < dist_to_y_boundary)
		tex = assign_textures1(coords, hit_y_mod, rays, game);
	else
	{
		coords->tex_x = (int)hit_x_mod;
		if (rays->sin_a > 0)
			tex = &game->north;
		else
			tex = &game->south;
	}
	return (tex);
}

void	init_coords(t_coords *coords, t_player *player,
	t_game *game, t_rays *rays)
{
	coords->dist = fixed_dist(player, rays, game);
	if (coords->dist <= 0.0000001)
		coords->dist = 0.0000001;
	coords->height = (BLOCK / coords->dist) * (game->screen_height / 2);
	coords->start_y = (game->screen_height - coords->height) / 2;
	if (coords->start_y < 0)
		coords->start_y = 0;
	coords->end_y = coords->start_y + coords->height;
	if (coords->end_y >= game->screen_height)
		coords->end_y = game->screen_height - 1;
}

void	apply_tex(t_texture *tex, t_coords *coords, int i, t_game *game)
{
	int	y;
	int	color;
	int	tex_y;

	coords->tex_x = (int)(coords->tex_x * (float)tex->width / BLOCK);
	if (coords->tex_x < 0)
		coords->tex_x = 0;
	if (coords->tex_x >= tex->width)
		coords->tex_x = tex->width - 1;
	y = coords->start_y;
	while (y < coords->end_y)
	{
		tex_y = ((y - coords->start_y) * tex->height) / coords->height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = get_texture_color(tex, coords->tex_x, tex_y);
		put_pixel(i, y, color, game);
		y++;
	}
}
