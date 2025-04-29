// #include "../includes/game.h"


// // void put_pixel(int x, int y, int color, t_game *game)
// // {
// //     if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
// //         return;
    
// //     int index = y * game->size_line + x * game->bpp / 8;
// //     game->data[index] = color & 0xFF;
// //     game->data[index + 1] = (color >> 8) & 0xFF;
// //     game->data[index + 2] = (color >> 16) & 0xFF;
// // }
// void put_pixel(int x, int y, int color, t_game *game)
// {
//     if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
//         return;

//     int index = y * game->size_line + x * (game->bpp / 8);
//     game->data[index + 0] = (color >> 16) & 0xFF; // Red
//     game->data[index + 2] = (color >> 8) & 0xFF;  // Green
//     game->data[index + 1] = color & 0xFF;         // Blue
// }



// void clear_image(t_game *game)
// {
//     for(int y = 0; y < HEIGHT; y++)
//         for(int x = 0; x < WIDTH; x++)
//             put_pixel(x, y, 0, game);
// }

// void draw_square(int x, int y, int size, int color, t_game *game)
// {
//     for(int i = 0; i < size; i++)
//         put_pixel(x + i, y, color, game);
//     for(int i = 0; i < size; i++)
//         put_pixel(x, y + i, color, game);
//     for(int i = 0; i < size; i++)
//         put_pixel(x + size, y + i, color, game);
//     for(int i = 0; i < size; i++)
//         put_pixel(x + i, y + size, color, game);
// }

// void draw_map(t_game *game)
// {
//     char **map = game->map;
//     int color = 0x57e422;
//     for(int y = 0; map[y]; y++)
//         for(int x = 0; map[y][x]; x++)
//             if(map[y][x] == '1')
//                 draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
// }

// float distance(float x, float y){
//     return sqrt(x * x + y * y);
// }

// float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
// {
//     float delta_x = x2 - x1;
//     float delta_y = y2 - y1;
//     float angle = atan2(delta_y, delta_x) - game->player.angle;
//     float fix_dist = distance(delta_x, delta_y) * cos(angle);
//     return fix_dist;
// }

// bool touch(float px, float py, t_game *game)
// {
//     int x = px / BLOCK;
//     int y = py / BLOCK;
//     if(game->map[y][x] == '1')
//         return true;
//     return false;
// }

// char **get_map(void)
// {
//     char **map = malloc(sizeof(char *) * 11);
//     map[0] = "111111111111111";
//     map[1] = "100000000000001";
//     map[2] = "100000000000001";
//     map[3] = "100000100000001";
//     map[4] = "100000000000001";
//     map[5] = "100000010000001";
//     map[6] = "100001000000001";
//     map[7] = "1000000000001";
//     map[8] = "100000000000001";
//     map[9] = "111111111111111";
//     map[10] = NULL;
//     return (map);
// }

// void init_game(t_game *game)
// {
//     init_player(&game->player);
//     game->map = get_map();
//     game->mlx = mlx_init();
//     game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
//     game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
//     game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
//     mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// }

// void draw_line(t_player *player, t_game *game, float start_x, int i)
// {
//     float cos_angle = cos(start_x);
//     float sin_angle = sin(start_x);
//     float ray_x = player->x;
//     float ray_y = player->y;

//     while(!touch(ray_x, ray_y, game))
//     {
//         if(DEBUG)
//             put_pixel(ray_x, ray_y, 0x57e422, game);
//         ray_x += cos_angle;
//         ray_y += sin_angle;
//     }
//     if(!DEBUG)
//     {
//         float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
//         float height = (BLOCK / dist) * (WIDTH / 2);
//         int start_y = (HEIGHT - height) / 2;
//         int end = start_y + height;
//         while(start_y < end)
//         {
//             put_pixel(i, start_y, 255, game);
//             start_y++;
//         }
//     }
// }

// // int draw_loop(t_game *game)
// // {
// //     t_player *player = &game->player;
// //     move_player(player);
// //     clear_image(game);
// //     if(DEBUG)
// //     {
// //         draw_square(player->x, player->y, 10, 0x00FF00, game);
// //         draw_map(game);
// //     }
// //     float fraction = PI / 3 / WIDTH;
// //     float start_x = player->angle - PI / 6;
// //     int i = 0;
// //     while(i < WIDTH)
// //     {
// //         draw_line(player, game, start_x, i);
// //         start_x += fraction;
// //         i++;
// //     }
// //     mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// //     return 0;
// // }

// // int main(void)
// // {
// //     t_game game;
// //     init_game(&game);
// //     mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
// //     mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
// //     mlx_loop_hook(game.mlx, draw_loop, &game);

// //     mlx_loop(game.mlx);
// //     return 0;
// // }

// int draw_loop(t_game *game)
// {
//     t_player *player = &game->player;
//     move_player(player, game);
//     clear_image(game);
//     if(DEBUG)
//     {
//         draw_square(player->x, player->y, 10, 0x00FF00, game);
//         draw_map(game);
//     }
//     float fraction = PI / 3 / WIDTH;
//     float start_x = player->angle - PI / 6;
//     int i = 0;
//     while(i < WIDTH)
//     {
//         draw_line(player, game, start_x, i);
//         start_x += fraction;
//         i++;
//     }
//     mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
//     return 0;
// }

// int main(void)
// {
//     t_game game;
//     init_game(&game);
//     mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
//     mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
//     mlx_hook(game.win, 6, 1L<<6, mouse_move, &game);
//     mlx_loop_hook(game.mlx, draw_loop, &game);
//     mlx_loop(game.mlx);
//     return 0;
// }
#include "../includes/game.h"

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

    for (int y = 0; map[y]; y++)
    {
        int row_len = strlen(map[y]);
        for (int x = 0; x < row_len; x++)
        {
            if (map[y][x] == '1')
            {
                int draw_x = offset_x - (row_len * scaled_block) + (x * scaled_block);
                int draw_y = offset_y + (y * scaled_block);
                draw_square(draw_x, draw_y, scaled_block, 0xaaaaaa, game);
            }
        }
    }

    int px = offset_x - (strlen(map[0]) * scaled_block) + (game->player.x * MINIMAP_SCALE);
    int py = offset_y + (game->player.y * MINIMAP_SCALE);
    draw_square(px - PLAYER_SIZE / 2, py - PLAYER_SIZE / 2, PLAYER_SIZE, 0xff0000, game);
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

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "1000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return map;
}

void init_game(t_game *game)
{
    init_player(&game->player);
    game->map = get_map();
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
        // float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
        // float height = (BLOCK / dist) * (WIDTH / 2);
        // int start_y = (HEIGHT - height) / 2;
        // int end_y = start_y + height;
        // for (int y = start_y; y < end_y; y++)
        //     put_pixel(i, y, 0xffffff, game);
        float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
    float height = (BLOCK / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - height) / 2;
    int end_y = start_y + height;

    // Choose correct x coordinate from the texture
    int tex_x = (int)((int)ray_x % BLOCK);
    if ((int)ray_y % BLOCK < (int)ray_x % BLOCK)
        tex_x = (int)((int)ray_y % BLOCK);

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

int main(void)
{
    t_game game;
    init_game(&game);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
    mlx_hook(game.win, 17, 0L, exit_game, &game); // Event for closing window (x button)
    mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
    mlx_loop_hook(game.mlx, draw_loop, &game);

    mlx_loop(game.mlx);
    return 0;
}