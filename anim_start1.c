/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_start1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:36:55 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/02 18:37:00 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* player.c */

#include "cub3D.h"

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

void move_player(t_player *player, t_game *game)
{
    float move_speed = 0.1;
    float rot_speed = 0.05;
    
    // Handle rotation
    if (player->left_rotate)
        player->angle -= rot_speed;
    if (player->right_rotate)
        player->angle += rot_speed;
    
    // Normalize angle
    if (player->angle < 0)
        player->angle += 2 * PI;
    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    
    // Calculate movement vectors
    float dx = cos(player->angle) * move_speed;
    float dy = sin(player->angle) * move_speed;
    
    // Handle forward/backward movement
    if (player->key_up)
    {
        float new_x = player->x + dx;
        float new_y = player->y + dy;
        
        if (!touch(new_x, player->y, game))
            player->x = new_x;
        if (!touch(player->x, new_y, game))
            player->y = new_y;
    }
    if (player->key_down)
    {
        float new_x = player->x - dx;
        float new_y = player->y - dy;
        
        if (!touch(new_x, player->y, game))
            player->x = new_x;
        if (!touch(player->x, new_y, game))
            player->y = new_y;
    }
    
    // Handle strafing movement
    if (player->key_left)
    {
        float strafe_dx = cos(player->angle - PI/2) * move_speed;
        float strafe_dy = sin(player->angle - PI/2) * move_speed;
        
        float new_x = player->x + strafe_dx;
        float new_y = player->y + strafe_dy;
        
        if (!touch(new_x, player->y, game))
            player->x = new_x;
        if (!touch(player->x, new_y, game))
            player->y = new_y;
    }
    if (player->key_right)
    {
        float strafe_dx = cos(player->angle + PI/2) * move_speed;
        float strafe_dy = sin(player->angle + PI/2) * move_speed;
        
        float new_x = player->x + strafe_dx;
        float new_y = player->y + strafe_dy;
        
        if (!touch(new_x, player->y, game))
            player->x = new_x;
        if (!touch(player->x, new_y, game))
            player->y = new_y;
    }
}

int exit_game(t_game *game)
{
    // Clean up resources
    if (game->img)
        mlx_destroy_image(game->mlx, game->img);
    if (game->wall_texture.img)
        mlx_destroy_image(game->mlx, game->wall_texture.img);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    
    // Free memory if needed
    // (map is managed elsewhere based on your code structure)
    
    exit(0);
    return (0);
}

int mouse_move(int x, int y, t_game *game)
{
    static int prev_x = -1;
    
    // Initialize prev_x on first call
    if (prev_x == -1)
    {
        prev_x = x;
        return (0);
    }
    
    // Ignore y-coordinate for now
    (void)y;
    
    // Calculate mouse movement and rotate player
    int delta_x = x - prev_x;
    if (delta_x != 0)
    {
        float rot_factor = 0.003;  // Adjust sensitivity as needed
        game->player.angle += delta_x * rot_factor;
        
        // Normalize angle
        if (game->player.angle < 0)
            game->player.angle += 2 * PI;
        if (game->player.angle > 2 * PI)
            game->player.angle -= 2 * PI;
        
        prev_x = x;
    }
    
    return (0);
}