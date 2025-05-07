/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:34:28 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/07 21:37:19 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_player_position(t_player *player, char **map, int x, int y)
{
	if (map[y][x] == 'N')
		player->angle = 3 * PI / 2;
	else if (map[y][x] == 'S')
		player->angle = PI / 2;
	else if (map[y][x] == 'E')
		player->angle = 0;
	else if (map[y][x] == 'W')
		player->angle = PI;
}

void	player_position(char **map, t_player *player)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
					|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				player->x = x * BLOCK + BLOCK / 2;
				player->y = y * BLOCK + BLOCK / 2;
				update_player_position(player, map, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_player *player, t_game *game)
{
	player_position(game->map, player);
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}
