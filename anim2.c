/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:55:49 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/03 17:53:23 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
int exit_game(t_game *game)
{
    // Free any allocated resources (textures, map, etc.)
    if (game->img)
        mlx_destroy_image(game->mlx, game->img);
    
    // Close the window
    mlx_destroy_window(game->mlx, game->win);
    

    exit(0);
}

void player_position(char **map, t_player *player)
{
    for (int y = 0; map[y]; y++)
    {
        for (int x = 0; map[y][x]; x++)
        {
            if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
            {
                // Center the player in the block
                player->x = x * BLOCK + BLOCK / 2;
                player->y = y * BLOCK + BLOCK / 2;

                if (map[y][x] == 'N')
                    player->angle = 3 * PI / 2; // 270 degrees
                else if (map[y][x] == 'S')
                    player->angle = PI / 2;     // 90 degrees
                else if (map[y][x] == 'E')
                    player->angle = 0;          // 0 degrees
                else if (map[y][x] == 'W')
                    player->angle = PI;         // 180 degrees

                return;
            }
        }
    }
}


void init_player(t_player *player, t_game *game)
{
    player_position(game->map, player);
    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;

    player->left_rotate = false;
    player->right_rotate = false;
}

int key_press(int keycode, t_player *player, t_game *game)
{
    if(keycode == W)
        player->key_up = true;
    if(keycode == S)
        player->key_down = true;
    if(keycode == A)
        player->key_left = true;
    if(keycode == D)
        player->key_right = true;
    if(keycode == LEFT)
        player->left_rotate = true;
    if(keycode == RIGHT)
        player->right_rotate = true;
    if(keycode == ESC)
        exit_game(game);  // Exit the game when 'Esc' is pressed
    return 0;
}


int key_release(int keycode, t_player *player)
{
    if(keycode == W)
        player->key_up = false;
    if(keycode == S)
        player->key_down = false;
    if(keycode == A)
        player->key_left = false;
    if(keycode == D)
        player->key_right = false;
    if(keycode == LEFT)
        player->left_rotate = false;
    if(keycode == RIGHT)
        player->right_rotate = false;
    return 0;
}

int is_walkable(float x, float y, t_game *game)
{
    int radius = 10;  // Radius of player (adjust as needed)

    int points[4][2] = {
        {(int)((x - radius) / BLOCK), (int)((y - radius) / BLOCK)},
        {(int)((x + radius) / BLOCK), (int)((y - radius) / BLOCK)},
        {(int)((x - radius) / BLOCK), (int)((y + radius) / BLOCK)},
        {(int)((x + radius) / BLOCK), (int)((y + radius) / BLOCK)}
    };

    for (int i = 0; i < 4; i++)
    {
        int tile_x = points[i][0];
        int tile_y = points[i][1];

        if (tile_y < 0 || game->map[tile_y] == NULL)
            return 0;

        int row_length = strlen(game->map[tile_y]);
        if (tile_x < 0 || tile_x >= row_length)
            return 0;

        if (game->map[tile_y][tile_x] == '1')
            return 0;
    }
    return 1;
}



void move_player(t_player *player, t_game *game)
{
    int speed = 5;
    float angle_speed = 0.03;
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);
    float new_x = player->x;
    float new_y = player->y;

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    if (player->key_up)
    {
        new_x += cos_angle * speed;
        new_y += sin_angle * speed;
    }
    if (player->key_down)
    {
        new_x -= cos_angle * speed;
        new_y -= sin_angle * speed;
    }
    if (player->key_left)
    {
        new_x += sin_angle * speed;
        new_y -= cos_angle * speed;
    }
    if (player->key_right)
    {
        new_x -= sin_angle * speed;
        new_y += cos_angle * speed;
    }

    if (is_walkable(new_x, new_y, game))
    {
        player->x = new_x;
        player->y = new_y;
    }
}

int mouse_move(int x, int y, t_game *game)
{
    (void)y;
    static int last_x = -1;
    float sensitivity = 0.003;

    if (last_x == -1)
        last_x = x;

    int delta_x = x - last_x;
    game->player.angle += delta_x * sensitivity;

    if (game->player.angle < 0)
        game->player.angle += 2 * PI;
    if (game->player.angle > 2 * PI)
        game->player.angle -= 2 * PI;

    last_x = x;
    return 0;
}