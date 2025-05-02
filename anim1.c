#include "cub3D.h"

void put_pixel(int x, int y, int color, t_game *game)
{
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;

    int index = y * game->size_line + x * (game->bpp / 8);
    game->data[index + 0] = (color >> 16) & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = color & 0xFF;
}

void clear_image(t_game *game)
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0x000000, game);
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
    for (int dy = 0; dy < size; dy++)
        for (int dx = 0; dx < size; dx++)
            put_pixel(x + dx, y + dy, color, game);
}

void draw_map(t_game *game)
{
    char **map = game->map;
    int color = 0x57e422;
    for (int y = 0; map[y]; y++)
        for (int x = 0; map[y][x]; x++)
            if (map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

void draw_minimap(t_game *game)
{
    char **map = game->map;
    int scaled_block = BLOCK * MINIMAP_SCALE;
    int offset_x = WIDTH - MINIMAP_PADDING;
    int offset_y = MINIMAP_PADDING;

    // Calculate minimap width and height
    int rows = 0;
    int cols = 0;
    while (map[rows])
    {
        int len = strlen(map[rows]);
        if (len > cols)
            cols = len;
        rows++;
    }
    int minimap_width = cols * scaled_block;
    int minimap_height = rows * scaled_block;

    // Draw minimap background
    for (int y = 0; y < minimap_height; y++)
    {
        for (int x = 0; x < minimap_width; x++)
        {
            int draw_x = offset_x - minimap_width + x;
            int draw_y = offset_y + y;
            put_pixel(draw_x, draw_y, 0x222222, game);  // dark gray background
        }
    }

    // Draw map tiles (walls and floor)
    for (int y = 0; y < rows; y++)
    {
        int row_len = strlen(map[y]);
        for (int x = 0; x < row_len; x++)
        {
            int draw_x = offset_x - minimap_width + (x * scaled_block);
            int draw_y = offset_y + (y * scaled_block);
            if (map[y][x] == '1')
                draw_square(draw_x, draw_y, scaled_block, 0xaaaaaa, game);  // walls
            else
                draw_square(draw_x, draw_y, scaled_block, 0x444444, game);  // floor (darker gray)
        }
    }

    // Draw player as a small red square
    int px = offset_x - minimap_width + (game->player.x * MINIMAP_SCALE);
    int py = offset_y + (game->player.y * MINIMAP_SCALE);
    draw_square(px - PLAYER_SIZE / 2, py - PLAYER_SIZE / 2, PLAYER_SIZE, 0xff0000, game);

    // Draw direction line
    float dir_x = cos(game->player.angle) * 10;
    float dir_y = sin(game->player.angle) * 10;
    for (int i = 0; i < 10; i++)
    {
        int dx = px + dir_x * (i / 10.0);
        int dy = py + dir_y * (i / 10.0);
        put_pixel(dx, dy, 0xff0000, game);
    }
}


float distance(float x, float y)
{
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float angle = atan2(dy, dx) - game->player.angle;
    return distance(dx, dy) * cos(angle);
}

bool touch(float px, float py, t_game *game)
{
    int x = px / BLOCK;
    int y = py / BLOCK;
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
    game->wall_texture.img = mlx_xpm_file_to_image(game->mlx, "/home/Cub3d/cub3d_42/src/no.xpm", &game->wall_texture.width, &game->wall_texture.height);
    if (!game->wall_texture.img)
    {
        printf("Failed to load texture\n");
        exit(1);
    }
    game->wall_texture.data = (int *)mlx_get_data_addr(game->wall_texture.img, &game->wall_texture.bpp, &game->wall_texture.size_line, &game->wall_texture.endian);
}

void draw_line(t_player *player, t_game *game, float angle, int i)
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

        int tex_x;
        if (fabsf(fmodf(ray_x, BLOCK)) < fabsf(fmodf(ray_y, BLOCK)))
            tex_x = (int)fmodf(ray_x, BLOCK);
        else
            tex_x = (int)fmodf(ray_y, BLOCK);

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

    float start_angle = player->angle - M_PI / 6;
    float step = (M_PI / 3) / WIDTH;
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
    mlx_hook(game.win, 17, 0L, exit_game, &game);
    mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
    mlx_loop_hook(game.mlx, draw_loop, &game);

    mlx_loop(game.mlx);
    return 0;
}
