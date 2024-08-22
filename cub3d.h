/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/22 16:46:24 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./utils/libft.h"
# include <stdio.h> //to be removed
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

#define WIDTH  1720
#define HEIGHT 740
#define TILE_SIZE 64
#define MINI_MAP_T 14
#define FOV 60 * (M_PI / 180)
#define SPEED 3
#define SPEED_MINI 1
#define TURN 3 * (M_PI / 180)

typedef struct s_texture
{
    int     flag;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     *f;
    int     *c;
}   t_texture;

typedef struct s_cube
{
    int    facing_up;
    int    facing_down;
    int    facing_right;
    int    facing_left;
    double true_distance;
	void	*mlx_win;
    void	*mlx;
    // mlx_image_t *img;
    mlx_image_t* image;
    mlx_texture_t* texture;
    char    **file;
    char    **map;
    char    *fd_file;
    int     map_len;
    int     file_len;
    t_texture textures;
    int     height;
    int     width;
    int     columx;
    int     columy;
    double     fd;
    int     playerX;
    int     playerY;
    double      speed_x;
    double      speed_y;
    double     player_X_pixel;
    double     player_Y_pixel;
    double player_angle;
    double  orizontal_position_x;
    double  orizontal_position_y;
    double  vertical_position_x;
    double  vertical_position_y;
    int  RIGHT_DOWN_RAYS;
    int  LEFT_DOWN_RAYS;
    int  RIGHT_UP_RAYS;
    int  LEFT_UP_RAYS;
}   t_cube;

// Parsing
void    parse_textures(t_cube *cube, int i);
void    parse_mape(t_cube *cube, char *tmp1, char **tmp2, int i);
int     parse_mape2(t_cube *cube);


//utils parsing
void    ft_init_texture(t_cube *cube);
void	is_map_valid(int argc, char *argv[], t_cube *cube);
void    get_element(t_cube *cube, char *str, char mode);
void    ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg);
void    take_map(t_cube *cube, int i, int j, int k);
void    ft_error(char *msg);
int just_space(char *str);


void	print_file(t_cube *cube);

// execution
void ft_randomize(void* param);
void ft_hook(void* param);

// mini_map

void draw_mini_map(t_cube *cube, mlx_image_t *image);

// utils execution
double	normalize_angle(double angle);
void ft_render_pixel(int32_t x, int32_t y, int32_t color, mlx_image_t *image);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void    rander_map(t_cube *cube, mlx_image_t *image);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void get_player_position(t_cube *cube);


// ray_casting
void ray_casting(t_cube *cube, mlx_image_t *image);
void draw_utils(t_cube *cube, mlx_image_t *image, double angle);
void render_wall(t_cube *cube, mlx_image_t *image, double angle, int ray);

#endif
