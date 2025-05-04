/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:21:38 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/04 18:48:24 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void handle_error(t_game *game, const char *message) {
    // Print the error message
    printf("Error: %s\n", message);
    
    // Clean up resources
    if (game) {
        // Free textures
        if (game->north.img) {
			free(game->north.data);
            mlx_destroy_image(game->mlx, game->north.img);
        }
        if (game->south.img) {
			free(game->south.data);
            mlx_destroy_image(game->mlx, game->south.img);
        }
        if (game->east.img) {
			free(game->east.data);
            mlx_destroy_image(game->mlx, game->east.img);
        }
        if (game->west.img) {
			free(game->west.data);
            mlx_destroy_image(game->mlx, game->west.img);
        }
        free(game->data);
        // Free dynamically allocated map if any
        if (game->map) {
            for (int i = 0; game->map[i] != NULL; i++) {
                free(game->map[i]);  // Free each row
            }
            free(game->map);  // Free the array of rows
        }

        // Destroy the main image
        if (game->img) {
            mlx_destroy_image(game->mlx, game->img);
        }

        // Close the window
        if (game->win) {
            mlx_destroy_window(game->mlx, game->win);
        }
    }

    // Exit the program
    exit(1);
}

float distance(float x, float y) {
    return (sqrt(x * x + y * y));
}

float fixed_dist(t_player *player, t_rays *rays, t_game *game) {
    float dx = rays->ray_x - player->x;
    float dy = rays->ray_y - player->y;
    float angle = atan2(dy, dx) - game->player.angle;
    return (distance(dx, dy) * cos(angle));
}

bool touch(float px, float py, t_game *game) {
    int x = px / BLOCK;
    int y = py / BLOCK;
    if (y < 0 || !game->map[y] || x < 0 || x >= (int)strlen(game->map[y])) {
        return true;
    }
    return game->map[y][x] == '1';
}

void safe_texture_load(t_game *game, t_texture *tex, char *path, char *name) {
	(void)name;
    if (!path) {
        handle_error(game, "Texture path not provided");
    }
    
    tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
    if (!tex->img) {
        handle_error(game, "Failed to load texture");
    }
    tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line, &tex->endian);
}

void load_textures(t_game *game, t_data *data) {
    safe_texture_load(game, &game->north, data->xpm_json.no_value, "NORTH");
    safe_texture_load(game, &game->south, data->xpm_json.so_value, "SOUTH");
    safe_texture_load(game, &game->east, data->xpm_json.ea_value, "EAST");
    safe_texture_load(game, &game->west, data->xpm_json.we_value, "WEST");
}

void calculate_window_size(t_game *game) {
    int max_width = 0;
    int max_height = 0;
    int display_w, display_h;

    // Calculate map dimensions
    while (game->map[max_height]) {
        int w = strlen(game->map[max_height]);
        if (w > max_width) max_width = w;
        max_height++;
    }

    // Get screen size
    mlx_get_screen_size(game->mlx, &display_w, &display_h);
    
    // Calculate required dimensions
    int required_width = max_width * BLOCK;
    int required_height = max_height * BLOCK;

    // Check size against display dimensions
    if (required_width > display_w - 100 || required_height > display_h - 100) {
        handle_error(game, "Map size exceeds screen size");
    }

    // Update screen size
    game->screen_width = required_width;
    game->screen_height = required_height;

    printf("Window size: %dx%d\n", game->screen_width, game->screen_height);
}

void init_game(t_game *game, t_data *data) {
    // Initialize MLX
	game->mlx = NULL;
    game->mlx = mlx_init();
    if (!game->mlx) {
        handle_error(game, "MLX initialization failed");
    }

    // Set map and ensure it is valid
    game->map = data->map;
    if (!game->map) {
        handle_error(game, "Map data is NULL");
    }

    // Calculate window size
    calculate_window_size(game);
    
    // Create window
    game->win = mlx_new_window(game->mlx, game->screen_width, game->screen_height, "Cub3D");
    if (!game->win) {
        handle_error(game, "Failed to create window");
    }

    // Create image
    game->img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
    if (!game->img) {
        handle_error(game, "Failed to create image");
    }

    // Get data address for the image
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    if (!game->data) {
        handle_error(game, "Failed to get image data address");
    }

    // Load textures
    load_textures(game, data);
    
    // Initialize player
    init_player(&game->player, game);
    if (game->player.x < 0 || game->player.y < 0) {
        handle_error(game, "Invalid player position");
    }

    // If you have RGB list
    game->rgb_lst = data->rgb_lst;
}

int start_anim(t_data *dbase) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));  // Initialize all fields to 0

    if (!dbase->map) {
        handle_error(&game, "Invalid map data");
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