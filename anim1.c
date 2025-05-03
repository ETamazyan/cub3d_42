/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:21:38 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/03 09:50:10 by etamazya         ###   ########.fr       */
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
	float	dy;
	float	angle;

	dx = rays->ray_x - player->x;
	dy = rays->ray_y - player->y;
	angle = atan2(dy, dx) - game->player.angle;
	return (distance(dx, dy) * cos(angle));
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (y < 0 || !game->map[y] || x < 0 || x >= (int)strlen(game->map[y]))
		return (true);
	return (game->map[y][x] == '1');
}

void	init_game(t_game *game, t_data *data)
{
	// printf("aaaaaaaaaaa %s\n", data->xpm_json.no_value);
	init_player(&game->player);
	game->map = data->map;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	game->wall_texture.img = mlx_xpm_file_to_image(game->mlx,
			data->xpm_json.no_value,
			&game->wall_texture.width, &game->wall_texture.height);
	if (!game->wall_texture.img)
	{
		printf("Error\nFailed to load texture\n");
		exit(1);
	}
	game->wall_texture.data = (int *)mlx_get_data_addr
		(game->wall_texture.img, &game->wall_texture.bpp,
			&game->wall_texture.size_line, &game->wall_texture.endian);
}

int	start_anim(t_data *dbase)
{
	t_game	game;

	if (!dbase->map)
	{
		printf("Error: Map is not valid.\n");
		return (1);
	}
	init_game(&game, dbase);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0L, exit_game, &game);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
