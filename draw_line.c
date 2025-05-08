/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:18:00 by by maavalya       #+#    #+#             */
/*   Updated: 2025/05/08 20:31:48 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_texture_color(t_texture *tex, int x, int y)
{
	// int	index;
	
	// if (!tex || !tex->data)
	// 	return (0);
	// if (tex_x < 0)
	// 	tex_x = 0;
	// if (tex_y < 0)
	// 	tex_y = 0;
	// if (tex_x >= tex->width)
	// 	tex_x = tex->width - 1;
	// if (tex_y >= tex->height)
	// 	tex_y = tex->height - 1;
	unsigned int	color;
	char			*dst;

	if(x >= 0 && x < tex->width && y >= 0 && y < tex->height)
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
	int			tex_y;
	int			color;
	t_texture	*tex;

	coords.dist = fixed_dist(player, rays, game);
	if (coords.dist <= 0.1)
		coords.dist = 0.1;
	coords.height = (BLOCK / coords.dist) * (game->screen_height / 2);
	coords.start_y = (game->screen_height - coords.height) / 2;
	if (coords.start_y < 0)
		coords.start_y = 0;
	coords.end_y = coords.start_y + coords.height;
	if (coords.end_y >= game->screen_height)
		coords.end_y = game->screen_height - 1;
	if (i < 0 || i >= game->screen_width)
	{
		printf("Warning: Attempted to draw column outside screen bounds: %d\n", i);
		return;
	}
	if (fabsf(fmodf(check_angle(rays->ray_x), BLOCK)) < fabsf(fmodf(check_angle(rays->ray_y), BLOCK)))
	{
		coords.tex_x = (int)fmodf((check_angle(rays->ray_x)), BLOCK);
		if (check_angle(rays->ray_y) > player->y)
			tex = &game->south;
		else
			tex = &game->north;
	}
	else
	{
		coords.tex_x = (int)fmodf((check_angle(rays->ray_y)), BLOCK);
		if (check_angle(rays->ray_x) > player->x)
			tex = &game->east;
		else
			tex = &game->west;
	}
	if (!tex || !tex->data)
	{
		printf("Warning: Invalid texture for column %d\n", i);
		y = coords.start_y;
		while (y < coords.end_y)
		{
			put_pixel(i, y, 0xFF0000, game);
			y++;
		}
		return;
	}
	coords.tex_x = (coords.tex_x + tex->width) % tex->width;
	if (coords.tex_x < 0)
		coords.tex_x = 0;
	if (coords.tex_x >= tex->width)
		coords.tex_x = tex->width - 1;
	y = coords.start_y;
	while (y < coords.end_y)
	{
		tex_y = ((y - coords.start_y) * tex->height) / coords.height;
		color = get_texture_color(tex, coords.tex_x, tex_y);
		put_pixel(i, y, color, game);
		y++;
	}
}

void draw_line(t_player *player, t_game *game, float angle, int i)
{
	t_rays	rays;
	int		steps;

	if (i < 0 || i >= game->screen_width)
	{
		printf("Warning: Attempted to draw column outside screen bounds: %d\n", i);
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

