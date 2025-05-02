/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:21:15 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/02 18:40:50 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

/**
 * Exits the game cleanly when the window is closed
 */
int exit_game(t_game *game)
{
    mlx_destroy_image(game->mlx, game->img);
    if (game->wall_texture.img)
        mlx_destroy_image(game->mlx, game->wall_texture.img);
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
    return (0);
}

/**
 * Handles mouse movement for camera rotation
 */
int mouse_move(int x, int y, t_game *game)
{
    static int prev_x = -1;
    
    (void)y; // Unused parameter
    
    if (prev_x == -1)
    {
        prev_x = x;
        return (0);
    }
    
    int delta_x = x - prev_x;
    game->player.angle += (delta_x * 0.005);
    
    // Normalize angle
    if (game->player.angle < 0)
        game->player.angle += 2 * PI;
    else if (game->player.angle > 2 * PI)
        game->player.angle -= 2 * PI;
    
    prev_x = x;
    return (0);
}

/**
 * Clears the image buffer
 */
void clear_image(t_game *game)
{
    int x;
    int y;
    
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            // Draw ceiling
            if (y < HEIGHT / 2)
                put_pixel(x, y, 0x87CEEB, game); // Sky blue
            // Draw floor
            else
                put_pixel(x, y, 0x8B4513, game); // Brown
            x++;
        }
        y++;
    }
}

/**
 * Draws a pixel to the image buffer
 */
void put_pixel(int x, int y, int color, t_game *game)
{
    char *dst;
    
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    
    dst = game->data + (y * game->size_line + x * (game->bpp / 8));
    *(unsigned int *)dst = color;
}

/**
 * Draws a square at the specified coordinates
 */
void draw_square(int x, int y, int size, int color, t_game *game)
{
    int i;
    int j;
    
    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            put_pixel(x + i, y + j, color, game);
            j++;
        }
        i++;
    }
}

/**
 * Draws the main map for debug mode
 */
void draw_map(t_game *game)
{
    int x;
    int y;
    
    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, 0xFFFFFF, game);
            x++;
        }
        y++;
    }
}

/**
 * Updates player movement based on key states
 */

void move_player(t_player *player, t_game *game)
{
    float move_speed = 4.0;
    float rotation_speed = 0.05;
    float new_x = player->x;
    float new_y = player->y;
    
    // Handle rotation
    if (player->left_rotate)
        player->angle -= rotation_speed;
    if (player->right_rotate)
        player->angle += rotation_speed;
    
    // Normalize angle
    if (player->angle < 0)
        player->angle += 2 * PI;
    else if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    
    // Calculate direction vectors
    float dx = cos(player->angle) * move_speed;
    float dy = sin(player->angle) * move_speed;
    
    // Handle movement
    if (player->key_up)
    {
        new_x += dx;
        new_y += dy;
    }
    if (player->key_down)
    {
        new_x -= dx;
        new_y -= dy;
    }
    if (player->key_left)
    {
        new_x += dy;
        new_y -= dx;
    }
    if (player->key_right)
    {
        new_x -= dy;
        new_y += dx;
    }
    
    // Check collisions and update position
    if (!touch(new_x, player->y, game))
        player->x = new_x;
    if (!touch(player->x, new_y, game))
        player->y = new_y;
}
void init_player(t_player *player)
{
    // Initialize player state
    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_right = false;
    player->left_rotate = false;
    player->right_rotate = false;
    
    // Default values will be overwritten by position finding in init_game
    player->angle = 0;
}
int key_release(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = false;
    else if (keycode == S)
        player->key_down = false;
    else if (keycode == A)
        player->key_left = false;
    else if (keycode == D)
        player->key_right = false;
    else if (keycode == LEFT)
        player->left_rotate = false;
    else if (keycode == RIGHT)
        player->right_rotate = false;
    
    return (0);
}

int key_press(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = true;
    else if (keycode == S)
        player->key_down = true;
    else if (keycode == A)
        player->key_left = true;
    else if (keycode == D)
        player->key_right = true;
    else if (keycode == LEFT)
        player->left_rotate = true;
    else if (keycode == RIGHT)
        player->right_rotate = true;
    
    return (0);
}