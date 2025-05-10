/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:18:00 by by maavalya       #+#    #+#             */
/*   Updated: 2025/05/10 18:49:04 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_texture_color(t_texture *tex, int x, int y)
{
	// int	index;
	
	// if (!tex || !tex->data)
	// 	return (0);
	// if (tex_x < 0)
	// 	tex_x = 0;
	// if (tex_y < 0)
	// 	tex_y = 0;
	// if (tex_x >= tex->width)
	// 	tex_x = tex->width - 1;
	// if (tex_y >= tex->height)
	// 	tex_y = tex->height - 1;
	unsigned int	color;
	char			*dst;

	if(x >= 0 && x < tex->width && y >= 0 && y < tex->height)
	{
		
		dst = tex->data + (y * tex->size_line + x * (tex->bpp / 8));
		color = *(unsigned int *)dst;
		return (color);
	}
	return (0);
}

// void	draw_line1(t_player *player, t_game *game, t_rays *rays, int i)
// {
// 	t_coords	coords;
// 	int			y;
// 	int			tex_y;
// 	int			color;
// 	t_texture	*tex;


// 	coords.dist = fixed_dist(player, rays, game);
// 	if (coords.dist <= 0.1)
// 		coords.dist = 0.1;
// 	coords.height = (BLOCK / coords.dist) * (game->screen_height / 2);
// 	coords.start_y = (game->screen_height - coords.height) / 2;
// 	if (coords.start_y < 0)
// 		coords.start_y = 0;
// 	coords.end_y = coords.start_y + coords.height;
// 	if (coords.end_y >= game->screen_height)
// 		coords.end_y = game->screen_height - 1;
// 	if (i < 0 || i >= game->screen_width)
// 	{
// 		printf("Warning: Attempted to draw column outside screen bounds: %d\n", i);
// 		return;
// 	}
// 	if (fabsf(fmodf(check_angle(rays->ray_x), BLOCK)) < fabsf(fmodf(check_angle(rays->ray_y), BLOCK)))
// 	{
// 		coords.tex_x = (int)fmodf(check_angle(rays->ray_x), BLOCK);
// 		if (check_angle(rays->ray_y) > player->y)
// 			tex = &game->south;
// 		else
// 			tex = &game->north;
// 	}
// 	else
// 	{
// 		coords.tex_x = (int)fmodf(check_angle(rays->ray_y), BLOCK);
// 		if (check_angle(rays->ray_x) > player->x)
// 			tex = &game->east;
// 		else
// 			tex = &game->west;
// 	}
// 	if (!tex || !tex->data)
// 	{
// 		printf("Warning: Invalid texture for column %d\n", i);
// 		y = coords.start_y;
// 		while (y < coords.end_y)
// 		{
// 			put_pixel(i, y, 0xFF0000, game);
// 			y++;
// 		}
// 		return;
// 	}
// 	coords.tex_x = (coords.tex_x + tex->width) % tex->width;
// 	if (coords.tex_x < 0)
// 		coords.tex_x = 0;
// 	if (coords.tex_x >= tex->width)
// 		coords.tex_x = tex->width - 1;
// 	y = coords.start_y;
// 	while (y < coords.end_y)
// 	{
// 		tex_y = ((y - coords.start_y) * tex->height) / coords.height;
// 		color = get_texture_color(tex, coords.tex_x, tex_y);
// 		put_pixel(i, y, color, game);
// 		y++;
// 	}
// }



// void draw_line(t_player *player, t_game *game, float angle, int i)
// {
// 	t_rays	rays;
// 	int		steps;

// 	if (i < 0 || i >= game->screen_width)
// 	{
// 		printf("Warning: Attempted to draw column outside screen bounds: %d\n", i);
// 		return ;
// 	}
// 	rays.ray_x = player->x;
// 	rays.ray_y = player->y;
// 	rays.cos_a = cos(angle);
// 	rays.sin_a = sin(angle);
// 	steps = 0;
// 	while (!touch(rays.ray_x, rays.ray_y, game) && steps < 1000)
// 	{
// 		if (DEBUG)
// 			put_pixel(rays.ray_x, rays.ray_y, 0xFFFFFF, game);
// 		rays.ray_x += rays.cos_a;
// 		rays.ray_y += rays.sin_a;
// 		steps++;
// 	}
// 	if (!DEBUG)
// 		draw_line1(player, game, &rays, i);
// }




void	draw_line1(t_player *player, t_game *game, t_rays *rays, int i, float ray_screen_angle)
{
    t_coords	coords;
    int			y;
    int			tex_y;
    int			color;
    t_texture	*tex;

	(void)ray_screen_angle; // Remove this line if you want to use ray_screen_angle in the calculations

	// Calculate distance from player to wall
	// coords.dist = distance(player->x, player->y, rays->ray_x, rays->ray_y);
	// Use fixed_dist function to calculate the distance
	// coords.dist = fixed_dist(player, rays, game);
    // // Apply fish-eye correction using the passed ray_screen_angle
    // float ray_angle_diff = ray_screen_angle - player->angle;
    // // Normalize the angle difference to [-PI, PI] for correct cosine calculation
    // if (ray_angle_diff > M_PI)
    //     ray_angle_diff -= 2 * M_PI;
    // if (ray_angle_diff < -M_PI)
    //     ray_angle_diff += 2 * M_PI;

	// 	coords.dist *= cos(ray_angle_diff); // Apply fisheye correction

    // if (coords.dist <= 0.1) // Prevent division by zero or very small numbers
    //     coords.dist = 0.1;

    // // Wall height calculation
    // coords.height = (BLOCK / coords.dist) * (game->screen_height / 2); // You may need to tune game->screen_height / 2
    // coords.start_y = (game->screen_height - coords.height) / 2;
    // if (coords.start_y < 0)
    //     coords.start_y = 0;
    // coords.end_y = coords.start_y + coords.height;
    // if (coords.end_y >= game->screen_height)
    //     coords.end_y = game->screen_height - 1;

		coords.dist = fixed_dist(player, rays, game);
	if (coords.dist <= 0.0000001)
		coords.dist = 0.0000001;
	coords.height = (BLOCK / coords.dist) * (game->screen_height / 2);
	coords.start_y = (game->screen_height - coords.height) / 2;
	if (coords.start_y < 0)
		coords.start_y = 0;
	coords.end_y = coords.start_y + coords.height;
	if (coords.end_y >= game->screen_height)
		coords.end_y = game->screen_height - 1;
    if (i < 0 || i >= game->screen_width)
    {
        printf("Warning: Attempted to draw column outside screen bounds: %d\n", i);
        return;
    }

    // Corrected tex_x calculation and texture selection
    float hit_x = rays->ray_x; // Final hit point X after ray traversal
    float hit_y = rays->ray_y; // Final hit point Y after ray traversal

    // Get the fractional part of the hit coordinate within a map block
    float hit_x_mod = fmodf(hit_x, BLOCK);
    float hit_y_mod = fmodf(hit_y, BLOCK);

    // Ensure positive modulo results, as fmodf can return negative for negative inputs
    if (hit_x_mod < 0)
        hit_x_mod += BLOCK;
    if (hit_y_mod < 0)
        hit_y_mod += BLOCK;

    // Determine which side of the wall was hit (East/West or North/South).
    // This heuristic compares the distance from the hit point to the nearest X-aligned grid line
    // versus the nearest Y-aligned grid line.
    float dist_to_x_boundary = fminf(hit_x_mod, BLOCK - hit_x_mod);
    float dist_to_y_boundary = fminf(hit_y_mod, BLOCK - hit_y_mod);

    if (dist_to_x_boundary < dist_to_y_boundary) // Ray hit an East/West wall (vertical grid line)
    {
        coords.tex_x = (int)hit_y_mod; // Use the Y-coordinate component for tex_x
        // Determine which specific texture (East or West) based on the ray's X direction
        if (rays->cos_a > 0) // Ray went right (X increased), hit a West-facing wall
            tex = &game->west;
        else // Ray went left (X decreased), hit an East-facing wall
            tex = &game->east;
    }
    else // Ray hit a North/South wall (horizontal grid line)
    {
        coords.tex_x = (int)hit_x_mod; // Use the X-coordinate component for tex_x
        // Determine which specific texture (North or South) based on the ray's Y direction
        if (rays->sin_a > 0) // Ray went down (Y increased), hit a North-facing wall
            tex = &game->north;
        else // Ray went up (Y decreased), hit a South-facing wall
            tex = &game->south;
    }

    if (!tex || !tex->data)
    {
        printf("Warning: Invalid texture for column %d\n", i);
        y = coords.start_y;
        while (y < coords.end_y)
        {
            put_pixel(i, y, 0xFF0000, game); // Draw a red line for missing texture
            y++;
        }
        return;
    }

    // Scale `coords.tex_x` to the texture's actual width.
    // This is essential if your `BLOCK` size (e.g., 32 world units) is different from your texture's pixel width (e.g., 64 pixels).
    coords.tex_x = (int)(coords.tex_x * (float)tex->width / BLOCK);

    // Clamp tex_x to be within texture bounds
    if (coords.tex_x < 0)
        coords.tex_x = 0;
    if (coords.tex_x >= tex->width)
        coords.tex_x = tex->width - 1;

    y = coords.start_y;
    while (y < coords.end_y)
    {
        // Calculate vertical texture coordinate (`tex_y`)
        // tex_y is a normalized position along the visible wall height, scaled to the texture's height
        tex_y = ((y - coords.start_y) * tex->height) / coords.height;
        // Clamp tex_y to be within texture bounds
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= tex->height)
            tex_y = tex->height - 1;

        color = get_texture_color(tex, coords.tex_x, tex_y);
        put_pixel(i, y, color, game);
        y++;
    }
}

void draw_line(t_player *player, t_game *game, float angle, int i)
{
    t_rays	rays;
    int		steps;

    if (i < 0 || i >= game->screen_width)
    {
        printf("Warning: Attempted to draw column outside screen bounds: %d\n", i);
        return ;
    }
    rays.ray_x = player->x;
    rays.ray_y = player->y;
    rays.cos_a = cos(angle);
    rays.sin_a = sin(angle);
    // We are NOT adding rays.ray_angle to t_rays as per your request.
    steps = 0;
    while (!touch(rays.ray_x, rays.ray_y, game) && steps < 1000)
    {
        if (DEBUG)
            put_pixel(rays.ray_x, rays.ray_y, 0xFFFFFF, game);
        rays.ray_x += rays.cos_a;
        rays.ray_y += rays.sin_a;
        steps++;
    }
    if (!DEBUG)
        draw_line1(player, game, &rays, i, angle); // Pass 'angle' as a new argument
}