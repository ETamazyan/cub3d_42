/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:34:25 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/02 18:38:31 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <string.h> // For strlen

void	draw_minimap(t_game *game)
{
	char		**map;
	t_new_type	things;

	map = game->map;
	things.scaled_block = BLOCK * MINIMAP_SCALE;
	things.offset_x = WIDTH - MINIMAP_PADDING;
	things.offset_y = MINIMAP_PADDING;
	things.y = 0;
	while (map[things.y])
	{
		things.x = 0;
		things.row_len = strlen(map[things.y]);
		while (things.x < things.row_len)
		{
			if (map[things.y][things.x] == '1')
			{
				things.draw_x = things.offset_x - (things.row_len * things.scaled_block)
					+ (things.x * things.scaled_block);
					things.draw_y = things.offset_y + (things.y * things.scaled_block);
				draw_square(things.draw_x, things.draw_y, things.scaled_block, 0xaaaaaa, game);
			}
			things.x++;
		}
		things.y++;
	}
	things.x = things.offset_x - (strlen(map[0]) * things.scaled_block)
		+ (game->player.x * MINIMAP_SCALE);
	things.y = things.offset_y + (game->player.y * MINIMAP_SCALE);
	draw_square(things.x - PLAYER_SIZE / 2, things.y - PLAYER_SIZE / 2,
		PLAYER_SIZE, 0xff0000, game);
}

float	distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	dx;
	float	dy;
	float	angle;

	dx = x2 - x1;
	dy = y2 - y1;
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
	init_player(&game->player);
	game->player.x = data->player.x * BLOCK;
	game->player.y = data->player.y * BLOCK;
	game->player.angle = 0;
	game->player.key_up = false;
	game->player.key_down = false;
	game->player.key_left = false;
	game->player.key_right = false;
	game->player.left_rotate = false;
	game->player.right_rotate = false;
	game->map = data->map;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	game->wall_texture.img = mlx_xpm_file_to_image(game->mlx,
			"/home/Cub3d/cub3d_42/src/no.xpm", &game->wall_texture.width,
			&game->wall_texture.height);
	if (!game->wall_texture.img)
	{
		printf("Failed to load texture\n");
		exit(1);
	}
	game->wall_texture.data = (int *)mlx_get_data_addr(game->wall_texture.img,
			&game->wall_texture.bpp, &game->wall_texture.size_line,
			&game->wall_texture.endian);
}

void	draw_line(t_player *player, t_game *game, float angle, int i)
{
	float ray_x = player->x;
	float ray_y = player->y;
	float cos_a = cos(angle);
	float sin_a = sin(angle);

	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0x57e422, game);
		ray_x += cos_a;
		ray_y += sin_a;
	}

	if (!DEBUG)
	{
		float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		float height = (BLOCK / dist) * (WIDTH / 2);
		int start_y = (HEIGHT - height) / 2;
		int end_y = start_y + height;

		// Choose correct x coordinate from the texture
		int tex_x = (int)((int)ray_x % BLOCK);
		if ((int)ray_y % BLOCK < (int)ray_x % BLOCK)
			tex_x = (int)((int)ray_y % BLOCK);

		for (int y = start_y; y < end_y; y++)
		{
			int tex_y = (y - start_y) * game->wall_texture.height / (end_y - start_y);
			int color = game->wall_texture.data[tex_y * game->wall_texture.width + tex_x];
			put_pixel(i, y, color, game);
		}
	}
}

int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(player, game);
	clear_image(game);

	if (DEBUG)
	{
		draw_square(player->x, player->y, 10, 0x00FF00, game);
		draw_map(game);
	}

	float start_angle = player->angle - PI / 6;
	float step = (PI / 3) / WIDTH;
	for (int i = 0; i < WIDTH; i++)
	{
		draw_line(player, game, start_angle, i);
		start_angle += step;
	}

	draw_minimap(game);

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

int start_anim(t_data *dbase)
{
    if (!dbase->map)
    {
        printf("Error: Map is not valid.\n");
        return 1;
    }
    t_game game;
    init_game(&game, dbase);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
    mlx_hook(game.win, 17, 0L, exit_game, &game); // Event for closing window (x button)
    mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
    mlx_loop_hook(game.mlx, draw_loop, &game);

    mlx_loop(game.mlx);
    return 0;
}