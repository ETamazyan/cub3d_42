/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:55:49 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/11 18:12:51 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	exit_game(t_game *game)
{
	int	i;

	if (game)
	{
		free_image(game);
		if (game->map)
		{
			i = 0;
			while (game->map[i] != NULL)
			{
				free(game->map[i]);
				i++;
			}
			free(game->map);
		}
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
	}
	exit(0);
}

int	key_press(int keycode, void *param)
{
	t_game		*game;
	t_player	*player;

	game = (t_game *)param;
	player = &game->player;
	if (keycode == W)
		player->key_up = 1;
	if (keycode == S)
		player->key_down = 1;
	if (keycode == A)
		player->key_left = 1;
	if (keycode == D)
		player->key_right = 1;
	if (keycode == LEFT)
		player->left_rotate = 1;
	if (keycode == RIGHT)
		player->right_rotate = 1;
	if (keycode == ESC)
		exit_game(game);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = 0;
	if (keycode == S)
		player->key_down = 0;
	if (keycode == A)
		player->key_left = 0;
	if (keycode == D)
		player->key_right = 0;
	if (keycode == LEFT)
		player->left_rotate = 0;
	if (keycode == RIGHT)
		player->right_rotate = 0;
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	int			delta_x;
	static int	last_x = -1;
	float		sensitivity;

	(void)y;
	sensitivity = 0.003;
	if (last_x == -1)
		last_x = x;
	delta_x = x - last_x;
	game->player.angle += delta_x * sensitivity;
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
	last_x = x;
	return (0);
}
