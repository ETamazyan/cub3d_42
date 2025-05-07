/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maavalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:21:38 by maavalya          #+#    #+#             */
/*   Updated: 2025/05/07 18:48:11 by maavalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_image(t_game *game)
{
	if (game->north.img)
		mlx_destroy_image(game->mlx, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx, game->south.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx, game->east.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx, game->west.img);
}

void	handle_error(t_game *game, const char *message)
{
	int	i;

	printf("Error: %s\n", message);
	if (game)
	{
		free_image(game);
		i = 0;
		if (game->map)
		{
			while (game->map[i] != NULL)
			{
				free(game->map[i]);
				i++;
			}
			free(game->map);
		}
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
	}
	exit (1);
}

void	calculate_window_size(t_game *game)
{
	int	max_width;
	int	max_height;
	int	display_w;
	int	display_h;
	int	w;

	max_width = 0;
	max_height = 0;
	while (game->map[max_height])
	{
		w = strlen(game->map[max_height]);
		if (w > max_width)
			max_width = w;
		max_height++;
	}
	mlx_get_screen_size(game->mlx, &display_w, &display_h);
	if (max_width * BLOCK > display_w - 100
		|| max_height * BLOCK > display_h - 100)
		handle_error(game, "Map size exceeds screen size");
	game->screen_width = max_width * BLOCK;
	game->screen_height = max_height * BLOCK;
	printf("Window size: %dx%d\n", game->screen_width, game->screen_height);
}

void	init_game(t_game *game, t_data *data)
{
	game->mlx = NULL;
	game->mlx = mlx_init();
	if (!game->mlx)
		handle_error(game, "MLX initialization failed");
	game->map = data->map;
	if (!game->map)
		handle_error(game, "Map data is NULL");
	calculate_window_size(game);
	game->win = mlx_new_window(game->mlx, game->screen_width,
			game->screen_height, "Cub3D");
	if (!game->win)
		handle_error(game, "Failed to create window");
	game->img = mlx_new_image(game->mlx,
			game->screen_width, game->screen_height);
	if (!game->img)
		handle_error(game, "Failed to create image");
	game->data = mlx_get_data_addr(game->img,
			&game->bpp, &game->size_line, &game->endian);
	if (!game->data)
		handle_error(game, "Failed to get image data address");
	load_textures(game, data);
	init_player(&game->player, game);
	if (game->player.x < 0 || game->player.y < 0)
		handle_error(game, "Invalid player position");
	game->rgb_lst = data->rgb_lst;
}

int	start_anim(t_data *dbase)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (!dbase->map)
		handle_error(&game, "Invalid map data");
	init_game(&game, dbase);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0L, exit_game, &game);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
