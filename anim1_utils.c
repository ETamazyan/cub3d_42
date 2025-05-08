/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim1_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:06:13 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/08 20:29:56 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_player *player, t_rays *rays, t_game *game)
{
	float	dx;
	float	angle;
	float	dy;

	dx = rays->ray_x - player->x;
	dy = rays->ray_y - player->y;
	(void)game;
	angle = atan2(dy, dx) - game->player.angle;
	return (distance(dx, dy) * cos(angle));
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (y < 0 || !game->map[y] || x < 0 || x >= (int)ft_strlen(game->map[y]))
		return (true);
	return (game->map[y][x] == '1');
}

void	safe_texture_load(t_game *game, t_texture *tex, char *path)
{
	if (!path)
		handle_error(game, "Texture path not provided");
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		handle_error(game, "Failed to load texture");
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line,
			&tex->endian);
}

void	load_textures(t_game *game, t_data *data)
{
	safe_texture_load(game, &game->north, data->xpm_json.no_value);
	safe_texture_load(game, &game->south, data->xpm_json.so_value);
	safe_texture_load(game, &game->east, data->xpm_json.ea_value);
	safe_texture_load(game, &game->west, data->xpm_json.we_value);
}
