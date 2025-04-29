#ifndef GAME_H
#define GAME_H

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 0

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 17
#define MINIMAP_SCALE 0.2
#define MINIMAP_PADDING 10
#define PLAYER_SIZE 4

# define PI 3.14159265359

#include "mlx.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef struct s_player
{
    float x;
    float y;
    float angle;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;

    bool left_rotate;
    bool right_rotate;
}   t_player;

typedef struct s_texture {
    void *img;
    int *data;
    int width;
    int height;
    int bpp;
    int size_line;
    int endian;
} t_texture;

typedef struct s_game
{
    void *mlx;
    void *win;
    void *img;
    t_texture wall_texture;

    char *data;
    int bpp;
    int size_line;
    int endian;
    t_player player;

    char **map;
} t_game;

void init_player(t_player *player);
int key_release(int keycode, t_player *player);
int key_press(int keycode, t_player *player, t_game *game);
// void move_player(t_player *player);
void move_player(t_player *player, t_game *game);
void clear_image(t_game *game);
void draw_square(int x, int y, int size, int color, t_game *game);
void draw_map(t_game *game);
void draw_line(t_player *player, t_game *game, float start_x, int i);
int exit_game(t_game *game);
int mouse_move(int x, int y, t_game *game);
#endif