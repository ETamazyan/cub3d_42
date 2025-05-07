/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:18:25 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/07 18:11:51 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define TEX_WIDTH 64
#define TEX_HEIGHT 64

/* Safe texture access function to prevent segfaults */
int get_texture_color(t_texture *tex, int tex_x, int tex_y) {
    /* Validate texture pointer */
    if (!tex || !tex->data) {
        return 0xFF0000; // Return red if texture is invalid
    }
    
    /* Clamp texture coordinates to valid range */
    if (tex_x < 0) tex_x = 0;
    if (tex_y < 0) tex_y = 0;
    if (tex_x >= tex->width) tex_x = tex->width - 1;
    if (tex_y >= tex->height) tex_y = tex->height - 1;
    
    /* Access texture data safely */
    int index = tex_y * tex->width + tex_x;
    if (index < 0 || index >= tex->width * tex->height) {
        return 0xFF0000; // Return red if out of bounds
    }
    
    return tex->data[index];
}

void draw_line1(t_player *player, t_game *game, t_rays *rays, int i) {
    t_coords    coords;
    int         y;
    int         tex_y;
    int         color;
    t_texture   *tex;

    /* Calculate ray distance and wall height */
	coords.dist = fixed_dist(player, rays, game);
	if (coords.dist <= 0.1) coords.dist = 0.1;
	float ray_angle = atan2f(rays->sin_a, rays->cos_a);

	// Apply fisheye correction
	float angle_diff = ray_angle - player->angle;

// Normalize between -PI and +PI
while (angle_diff > M_PI) angle_diff -= 2 * M_PI;
while (angle_diff < -M_PI) angle_diff += 2 * M_PI;

	
	// Calculate wall height
	coords.height = (BLOCK / coords.dist) * (game->screen_height / 2);
	
    coords.start_y = (game->screen_height - coords.height) / 2;
    if (coords.start_y < 0) coords.start_y = 0;
    
    coords.end_y = coords.start_y + coords.height;
    if (coords.end_y >= game->screen_height) coords.end_y = game->screen_height - 1;

    /* Check if i is within screen bounds */
    if (i < 0 || i >= game->screen_width) {
        printf("Warning: Attempted to draw column outside screen bounds: %d\n", i);
        return;
    }

    /* Determine which texture to use based on wall orientation */
    // (Include the existing logic here...)
    if (fabsf(fmodf(rays->ray_x, BLOCK)) < fabsf(fmodf(rays->ray_y, BLOCK))) {
        coords.tex_x = (int)fmodf(rays->ray_x, BLOCK);
        if (rays->ray_y > player->y)
            tex = &game->south;
        else
            tex = &game->north;
    } else {
        coords.tex_x = (int)fmodf(rays->ray_y, BLOCK);
        if (rays->ray_x > player->x)
            tex = &game->east;
        else
            tex = &game->west;
    }

    /* Validate texture */
    if (!tex || !tex->data) {
        printf("Warning: Invalid texture for column %d\n", i);
        /* Draw solid color column instead */
        for (y = coords.start_y; y < coords.end_y; y++) {
            put_pixel(i, y, 0xFF0000, game); // Red for error
        }
        return;
    }

    /* Ensure tex_x is within bounds */
    coords.tex_x = (coords.tex_x + tex->width) % tex->width;
    if (coords.tex_x < 0) coords.tex_x = 0;
    if (coords.tex_x >= tex->width) coords.tex_x = tex->width - 1;

    /* Draw textured wall column */
    y = coords.start_y;
    while (y < coords.end_y) {
        tex_y = ((y - coords.start_y) * tex->height) / coords.height; // Adjusted for wall height
        color = get_texture_color(tex, coords.tex_x, tex_y);
        put_pixel(i, y, color, game);
        y++;
    }
}
// void draw_line1(t_player *player, t_game *game, t_rays *rays, int i) {
//     t_coords    coords;
//     int         y;
//     int         tex_y;
//     int         color;
//     t_texture   *tex;

//     /* Calculate ray distance and wall height */
//     coords.dist = fixed_dist(player, rays, game);
//     if (coords.dist <= 0.1) {
//         coords.dist = 0.1; // Prevent division by zero
//     }
    
//     /* Calculate wall height */
//     coords.height = (BLOCK / coords.dist) * (game->screen_width / 2);
//     coords.start_y = (game->screen_height - coords.height) / 2;
//     if (coords.start_y < 0) coords.start_y = 0;
    
//     coords.end_y = coords.start_y + coords.height;
//     if (coords.end_y >= game->screen_height) coords.end_y = game->screen_height - 1;

//     /* Check if i is within screen bounds */
//     if (i < 0 || i >= game->screen_width) {
//         printf("Warning: Attempted to draw column outside screen bounds: %d\n", i);
//         return;
//     }

//     /* Determine which texture to use based on wall orientation */
//     if (rays->ray_x == 0 && rays->ray_y == 0) {
//         printf("Warning: Invalid ray position at column %d\n", i);
//         return;
//     }

//     /* Determine which texture to use based on wall orientation */
//     if (fabsf(fmodf(rays->ray_x, BLOCK)) < fabsf(fmodf(rays->ray_y, BLOCK))) {
//         coords.tex_x = (int)fmodf(rays->ray_x, BLOCK);
//         if (rays->ray_y > player->y)
//             tex = &game->south;
//         else
//             tex = &game->north;
//     } else {
//         coords.tex_x = (int)fmodf(rays->ray_y, BLOCK);
//         if (rays->ray_x > player->x)
//             tex = &game->east;
//         else
//             tex = &game->west;
//     }

//     /* Validate texture */
//     if (!tex || !tex->data) {
//         printf("Warning: Invalid texture for column %d\n", i);
//         /* Draw solid color column instead */
//         for (y = coords.start_y; y < coords.end_y; y++) {
//             put_pixel(i, y, 0xFF0000, game); // Red for error
//         }
//         return;
//     }

//     /* Ensure tex_x is within bounds */
//     coords.tex_x = (coords.tex_x + tex->width) % tex->width;
//     if (coords.tex_x < 0) coords.tex_x = 0;
//     if (coords.tex_x >= tex->width) coords.tex_x = tex->width - 1;

//     /* Draw textured wall column */
//     y = coords.start_y;
//     while (y < coords.end_y) {
//         /* Calculate texture y-coordinate with bounds checking */
//         if (coords.end_y == coords.start_y) {
//             tex_y = 0;
//         } else {
//             tex_y = ((y - coords.start_y) * tex->height) / (coords.end_y - coords.start_y);
//         }
        
//         /* Ensure tex_y is within bounds */
//         if (tex_y < 0) tex_y = 0;
//         if (tex_y >= tex->height) tex_y = tex->height - 1;
        
//         /* Use safe texture access */
//         color = get_texture_color(tex, coords.tex_x, tex_y);
        
//         /* Draw pixel */
//         put_pixel(i, y, color, game);
//         y++;
//     }
// }

void draw_line(t_player *player, t_game *game, float angle, int i) {
    t_rays  rays;

    /* Check if i is within screen bounds */
    if (i < 0 || i >= game->screen_width) {
        printf("Warning: Attempted to draw column outside screen bounds: %d\n", i);
        return;
    }

    /* Initialize ray position and direction */
    rays.ray_x = player->x;
    rays.ray_y = player->y;
    rays.cos_a = cos(angle);
    rays.sin_a = sin(angle);
    
    /* Cast ray until it hits a wall */
    int max_distance = 1000; // Prevent infinite loops
    int steps = 0;
    
    while (!touch(rays.ray_x, rays.ray_y, game) && steps < max_distance) {
        if (DEBUG)
            put_pixel(rays.ray_x, rays.ray_y, 0xFFFFFF, game);
        rays.ray_x += rays.cos_a;
        rays.ray_y += rays.sin_a;
        steps++;
    }
    
    if (!DEBUG)
        draw_line1(player, game, &rays, i);
}

/* 
 * Modified load_texture function to ensure texture data is properly initialized
 * and stored once at program start
 */
void load_texture(t_game *game, void **img, int **data, char *path, char *name) {
    int width, height;
    
    if (!path) {
        printf("Error: %s texture path is NULL\n", name);
        exit(1);
    }
    
    printf("Loading texture %s from path: %s\n", name, path);
    
    /* Try to load the texture */
    *img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
    if (!*img) {
        printf("Error: Failed to load %s texture at path: %s\n", name, path);
        
        /* Create fallback texture */
        printf("Creating fallback texture for %s\n", name);
        *img = mlx_new_image(game->mlx, TEX_WIDTH, TEX_HEIGHT);
        if (!*img) {
            printf("Critical error: Failed to create fallback texture\n");
            exit(1);
        }
        
        /* Get data address for the new image */
        *data = (int *)mlx_get_data_addr(*img, &game->bpp, &game->size_line, &game->endian);
        
        /* Fill with a solid color */
        for (int y = 0; y < TEX_HEIGHT; y++) {
            for (int x = 0; x < TEX_WIDTH; x++) {
                (*data)[y * TEX_WIDTH + x] = 0xFF0000; // Red for missing texture
            }
        }
        
        /* Set texture dimensions */
        if (name[0] == 'n') {
            game->north.width = TEX_WIDTH;
            game->north.height = TEX_HEIGHT;
        } else if (name[0] == 's') {
            game->south.width = TEX_WIDTH;
            game->south.height = TEX_HEIGHT;
        } else if (name[0] == 'e') {
            game->east.width = TEX_WIDTH;
            game->east.height = TEX_HEIGHT;
        } else if (name[0] == 'w') {
            game->west.width = TEX_WIDTH;
            game->west.height = TEX_HEIGHT;
        }
        
        return;
    }
    
    /* Texture loaded successfully */
    printf("Texture %s loaded successfully (%dx%d)\n", name, width, height);
    
    /* Get texture data */
    *data = (int *)mlx_get_data_addr(*img, &game->bpp, &game->size_line, &game->endian);
    if (!*data) {
        printf("Error: Failed to get %s texture data\n", name);
        mlx_destroy_image(game->mlx, *img);
        *img = NULL;
        exit(1);
    }
    
    /* Set texture dimensions in the appropriate texture struct */
    if (name[0] == 'n') {
        game->north.width = width;
        game->north.height = height;
    } else if (name[0] == 's') {
        game->south.width = width;
        game->south.height = height;
    } else if (name[0] == 'e') {
        game->east.width = width;
        game->east.height = height;
    } else if (name[0] == 'w') {
        game->west.width = width;
        game->west.height = height;
    }
}