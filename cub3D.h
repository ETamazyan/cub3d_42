/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:04:34 by etamazya          #+#    #+#             */
/*   Updated: 2025/05/05 21:08:07 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>
// # define WIDTH 2000   
// # define HEIGHT 2000
# define BLOCK 32
# define DEBUG 0

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307
#define MINIMAP_SCALE 0.2
#define MINIMAP_PADDING 10
#define PLAYER_SIZE 4

# define PI 3.14159265359

// #include "mlx.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
//shortening the code

typedef struct s_rays
{
	float ray_x;
	float ray_y;
	float cos_a;
	float sin_a;
} t_rays;

typedef struct s_coords
{
	float dist;
	float height;
	int start_y;
	int end_y;
	int tex_x;
}	t_coords;

typedef struct s_pixel
{
    int x;
    int y;
    int color;
}               t_pixel;

typedef struct s_draw
{
    int dx;
    int dy;
    int size;
    int color;
}               t_draw;

typedef struct s_minimap
{
    int scaled_block;
    int offset_x;
    int offset_y;
    int rows;
    int cols;
    int minimap_width;
    int minimap_height;
}               t_minimap;

typedef struct s_tex
{
    int tex_x;
    int tex_y;
    int start_y;
    int end_y;
    float height;
}               t_tex;
//
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

typedef struct s_rgb
{
	int				cR;
	int				fR;
	int				cG;
	int				fG;
	int				cB;
	int				fB;
}					t_rgb;


typedef struct s_game
{
    // //added for door
    // void	*img_1;
    // // end_here
    void *mlx;
    void *win;
    void *img;
    t_texture wall_texture;
	t_texture north;
	t_texture south;
	t_texture east;
	t_texture west;
    t_rgb	rgb_lst;
    char *data;
    int bpp;
    int size_line;
    int endian;
    t_player player;
    int screen_width;
    int screen_height;
    char **map;
} t_game;



/* New type for minimap rendering */
typedef struct s_new_type
{
    int x;
    int y;
    int draw_x;
    int draw_y;
    int row_len;
    int scaled_block;
    int offset_x;
    int offset_y;
} t_new_type;

typedef struct s_pos
{
	char			*direction;
	int				x;
	int				y;
}					t_pos;

typedef struct s_xpm
{
	char		*no_value;
	char		*so_value;
	char		*we_value;
	char		*ea_value;
}				t_xpm;

typedef struct s_data
{
    char			**map;
    t_xpm			xpm_json;
	t_pos			player;
	t_rgb			rgb_lst;
}   t_data;


void put_pixel(int x, int y, int color, t_game *game);
void clear_image(t_game *game);
void draw_square(t_draw draw, t_game *game);
void draw_map(t_game *game);
void draw_minimap(t_game *game);
float distance(float x, float y);
float fixed_dist(t_player *player, t_rays *rays, t_game *game);
bool touch(float px, float py, t_game *game);
void init_game(t_game *game, t_data *data);
void draw_line(t_player *player, t_game *game, float angle, int i);
int draw_loop(t_game *game);
int start_anim(t_data *data);

void init_player(t_player *player, t_game *game);
int key_release(int keycode, t_player *player);
int key_press(int keycode, t_player *player, t_game *game);
// void move_player(t_player *player);
void move_player(t_player *player, t_game *game);
void clear_image(t_game *game);
void clean_dbl_chr_ptr(char **lines);


int exit_game(t_game *game);
void handle_error(t_game *game, const char *message); // Print exit message
int mouse_move(int x, int y, t_game *game);


/* validation and map creation */
int		valid_and_parsing(t_data *dbase, char *filename);
void	valid_fd_filename(t_data *dbase, int fd, char *filename);
char	*initialize_buf(int fd);
void	only_whitespace(t_data *dbase, char *res);
int valid_whole_file_keep_data(char **lines, t_data *dbase, int count); // if 1 error

// error.c
void print_err_exit(t_data *data, char *msg);
void	clean_data(t_data *data);

// valid_helpers.c
int	is_texture(char *line);
int	is_color(char *line);
int	is_map_line(char *line);
int check_keep_xpm(t_data *dbase, char *line);

// helper functions
size_t	ft_startlen(const char *s1, const char *set);
int		ft_check2(char const *set, char const str);
char	*check_newline2(char *join);
char	*ft_strtrim(char const *s1, char const *set);
void	check_whitespaces(char **res);
void	check_newline(char *join);
void	check_whitespaces(char **res);
char	*check_newline2(char *join);
int		ft_check2(char const *set, char const str);
size_t	ft_startlen(const char *s1, const char *set);
int		ft_size(int start, int end);
char	*ft_strtrim2(char *s1, char *set);
int check_res(t_data *t_dbase, char *string, char *buf);


// rgb validation parsing
int		keep_check_rgb(t_data *db, char *line);
int		keep_rgb(int *r, int *g, int *b, char *line);
void	check_rgb(t_data *dbase, int r, int g, int b);

// map validation
char	*cut_front(char *old);
int keep_valid_map(char **lines, t_data *dbase);
void init_dbase(t_data *dbase);

/* helpers */
void	free_str_array(char **arr);
void	free_res(char *buf, char *res);
char *ft_strncpy_malloc(const char *src, int n);

// utils
char    **ft_strdup_2d(char **s1, int index);

// checkers
int	check(char s);
int check_disordered_wall(char **map, int j, int i);
int check_side_walls(char **map, int i, int j);
int check_walls(char **map);
int check_chars(char **map);
void clean_map(char **map);
int check_player(char **map);
int check_door(char **map);

#endif