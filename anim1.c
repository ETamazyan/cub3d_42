/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:21:38 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/02 20:18:13 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float distance(float x, float y)
{
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float dx;
    float dy;
    float angle;

    dx = x2 - x1;
    dy = y2 - y1;
    angle = atan2(dy, dx) - game->player.angle;
    return distance(dx, dy) * cos(angle);
}

bool touch(float px, float py, t_game *game)
{
    int x;
    int y;

    x = px / BLOCK;
    y = py / BLOCK;
    if (y < 0 || !game->map[y] || x < 0 || x >= (int)strlen(game->map[y]))
        return true;
    return game->map[y][x] == '1';
}

void init_game(t_game *game, t_data *data)
{
    init_player(&game->player);
    game->map = data->map;
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    game->wall_texture.img = mlx_xpm_file_to_image(game->mlx, "/home/Cub3d/cub3d_42/src/no.xpm",
                                                   &game->wall_texture.width, &game->wall_texture.height);
    if (!game->wall_texture.img)
    {
        printf("Failed to load texture\n");
        exit(1);
    }
    game->wall_texture.data = (int *)mlx_get_data_addr(game->wall_texture.img, &game->wall_texture.bpp,
                                                        &game->wall_texture.size_line, &game->wall_texture.endian);
}


int draw_loop(t_game *game)
{
    t_player *player;
    float start_angle;
    float step;
    int i;
	t_draw draw;

    player = &game->player;
    move_player(player, game);
    clear_image(game);

    if (DEBUG)
    {
		draw.dx = player->x;
		draw.dy = player->y;
		draw.size = 10;
		draw.color = 0x00FF00;
		draw_square(draw, game);
        draw_map(game);
    }

    start_angle = player->angle - M_PI / 6;
    step = (M_PI / 3) / WIDTH;
    i = 0;
    while (i < WIDTH)
    {
        draw_line(player, game, start_angle, i);
        start_angle += step;
        i++;
    }

    draw_minimap(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}

int start_anim(t_data *dbase)
{
    t_game game;

    if (!dbase->map)
    {
        printf("Error: Map is not valid.\n");
        return 1;
    }
    init_game(&game, dbase);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
    mlx_hook(game.win, 17, 0L, exit_game, &game);
    mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);
    return 0;
}
