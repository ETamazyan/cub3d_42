/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:36:17 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/07 21:36:24 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_if(int tile_x, int tile_y, t_game *game)
{
	if (tile_y < 0 || game->map[tile_y] == NULL)
		return (0);
	if (tile_x < 0 || tile_x >= (int)ft_strlen(game->map[tile_y]))
		return (0);
	if (game->map[tile_y][tile_x] == '1')
		return (0);
	return (1);
}

int	is_walkable(float x, float y, t_game *game)
{
	int	i;
	int	tile_x;
	int	tile_y;
	int	points[4][2];

	points[0][0] = (int)((x - 10) / BLOCK);
	points[0][1] = (int)((y - 10) / BLOCK);
	points[1][0] = (int)((x + 10) / BLOCK);
	points[1][1] = (int)((y - 10) / BLOCK);
	points[2][0] = (int)((x - 10) / BLOCK);
	points[2][1] = (int)((y + 10) / BLOCK);
	points[3][0] = (int)((x + 10) / BLOCK);
	points[3][1] = (int)((y + 10) / BLOCK);
	i = 0;
	while (i < 4)
	{
		tile_x = points[i][0];
		tile_y = points[i][1];
		if (check_if(tile_x, tile_y, game) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	init_new_coords(float *new_x, float *new_y, t_player *player)
{
	float	speed;

	speed = 1.5;
	if (player->key_up)
	{
		*new_x += cos(player->angle) * speed;
		*new_y += sin(player->angle) * speed;
	}
	if (player->key_down)
	{
		*new_x -= cos(player->angle) * speed;
		*new_y -= sin(player->angle) * speed;
	}
	if (player->key_left)
	{
		*new_x += sin(player->angle) * speed;
		*new_y -= cos(player->angle) * speed;
	}
	if (player->key_right)
	{
		*new_x -= sin(player->angle) * speed;
		*new_y += cos(player->angle) * speed;
	}
}

void	init_player_angle(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.03;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void	move_player(t_player *player, t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = player->x;
	new_y = player->y;
	init_player_angle(player);
	init_new_coords(&new_x, &new_y, player);
	if (is_walkable(new_x, new_y, game))
	{
		player->x = new_x;
		player->y = new_y;
	}
}
