/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:21:38 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/03 17:42:41 by maavalya         ###   ########.fr       */
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim1.c                                            :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Add these to your t_game struct definition in cub3D.h:
/*
typedef struct s_game {
    // ... existing fields ...
    int screen_width;
    int screen_height;
    // ... rest of your struct ...
} t_game;
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim1.c                                            :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void safe_texture_load(t_game *game, t_texture *tex, char *path, char *name)
{
    if (!path) {
        printf("Error: %s texture path not provided\n", name);
        exit(1);
    }
    
    tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
    if (!tex->img) {
        printf("Error: Failed to load %s texture at %s\n", name, path);
        exit(1);
    }
    tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line, &tex->endian);
}

void calculate_window_size(t_game *game)
{
    int max_width = 0;
    int max_height = 0;
    int display_w, display_h;
    
    // Calculate map dimensions
    while (game->map[max_height]) {
        int w = strlen(game->map[max_height]);
        if (w > max_width) max_width = w;
        max_height++;
    }
    
    // Get screen size and apply limits
    mlx_get_screen_size(game->mlx, &display_w, &display_h);
    game->screen_width = fmin(max_width * BLOCK, display_w - 100);
    game->screen_height = fmin(max_height * BLOCK, display_h - 100);
    
    // Minimum size constraints
    game->screen_width = fmax(game->screen_width, 400);
    game->screen_height = fmax(game->screen_height, 300);
    
    printf("Window size: %dx%d\n", game->screen_width, game->screen_height);
}

void init_game(t_game *game, t_data *data)
{
    // Initialize MLX first
    game->mlx = mlx_init();
    if (!game->mlx) {
        printf("Error: MLX initialization failed\n");
        exit(1);
    }

    // Set map and calculate window size
    game->map = data->map;
    calculate_window_size(game);
    
    // Create window and image
    game->win = mlx_new_window(game->mlx, game->screen_width, game->screen_height, "Cub3D");
    game->img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    
    // Load textures with validation
    safe_texture_load(game, &game->north, data->xpm_json.no_value, "NORTH");
    safe_texture_load(game, &game->south, data->xpm_json.so_value, "SOUTH");
    safe_texture_load(game, &game->east, data->xpm_json.ea_value, "EAST");
    safe_texture_load(game, &game->west, data->xpm_json.we_value, "WEST");
    
    // Initialize player with position validation
    init_player(&game->player, game);
    if (game->player.x < 0 || game->player.y < 0) {
        printf("Error: Invalid player position\n");
        exit(1);
    }
    
    game->rgb_lst = data->rgb_lst;
}

int start_anim(t_data *dbase)
{
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));  // Initialize all fields to 0

    if (!dbase->map) {
        printf("Error: Invalid map data\n");
        return 1;
    }

    init_game(&game, dbase);
    
    // Set up event hooks
    mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
    mlx_hook(game.win, 17, 0L, exit_game, &game);
    mlx_hook(game.win, 6, 1L<<6, mouse_move, &game);
    
    // Start main loop
    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);
    
    return 0;
}