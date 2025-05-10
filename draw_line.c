/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:18:00 by by maavalya       #+#    #+#             */
/*   Updated: 2025/05/10 19:46:02 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_texture_color(t_texture *tex, int x, int y)
{
	unsigned int	color;
	char			*dst;

	if (x >= 0 && x < tex->width && y >= 0 && y < tex->height)
	{
		dst = tex->data + (y * tex->size_line + x * (tex->bpp / 8));
		color = *(unsigned int *)dst;
		return (color);
	}
	return (0);
}

void	draw_line1(t_player *player, t_game *game, t_rays *rays, int i)
{
	t_coords	coords;
	int			y;
	t_texture	*tex;

	tex = NULL;
	init_coords(&coords, player, game, rays);
	if (i < 0 || i >= game->screen_width)
	{
		printf("Warning: Column outside screen bounds: %d\n", i);
		return ;
	}
	tex = assign_textures(rays, game, tex, &coords);
	if (!tex || !tex->data)
	{
		printf("Warning: Invalid texture for column %d\n", i);
		y = coords.start_y;
		while (y < coords.end_y)
		{
			put_pixel(i, y, 0xFF0000, game);
			y++;
		}
		return ;
	}
	apply_tex(tex, &coords, i, game);
}

void	draw_line(t_player *player, t_game *game, float angle, int i)
{
	t_rays	rays;
	int		steps;

	if (i < 0 || i >= game->screen_width)
	{
		printf("Warning: Column outside screen bounds: %d\n", i);
		return ;
	}
	rays.ray_x = player->x;
	rays.ray_y = player->y;
	rays.cos_a = cos(angle);
	rays.sin_a = sin(angle);
	steps = 0;
	while (!touch(rays.ray_x, rays.ray_y, game) && steps < 1000)
	{
		if (DEBUG)
			put_pixel(rays.ray_x, rays.ray_y, 0xFFFFFF, game);
		rays.ray_x += rays.cos_a;
		rays.ray_y += rays.sin_a;
		steps++;
	}
	if (!DEBUG)
		draw_line1(player, game, &rays, i);
}
