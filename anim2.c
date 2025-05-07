/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:55:49 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/07 21:36:11 by maavalya         ###   ########.fr       */
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

int	key_press(int keycode, t_player *player, t_game *game)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == ESC)
		exit_game(game);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
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
