/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/15 19:45:43 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/syslimits.h>

static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


void get_player_position(t_cube *cube)
{
    int x = 0;
    int y = 0;
    while (cube->map[y])
    {
        x = 0;
        while (cube->map[y][x])
        {
            if (cube->map[y][x] == 'W')
            {
                cube->player_X_pixel = x * TILE_SIZE + TILE_SIZE / 2;
                cube->player_Y_pixel = y * TILE_SIZE + TILE_SIZE / 2;
                cube->playerX = x;
                cube->playerY = y;
                return ;
            }
            x++;
        }
        y++;
    }
}
void ft_render_pixel_player(int32_t color, t_cube *cube)
{
    int i, j;
    // int title;
  
    // Draw a circle for the player
    for (i = 0; i < TILE_SIZE / 5; i++)
    {
        for (j = 0; j < TILE_SIZE / 5; j++)
        {
            mlx_put_pixel(image, cube->player_X_pixel + i, cube->player_Y_pixel + j, color);
            mlx_put_pixel(image, cube->player_X_pixel - i, cube->player_Y_pixel + j, color);
            mlx_put_pixel(image, cube->player_X_pixel + i, cube->player_Y_pixel - j, color);
            mlx_put_pixel(image, cube->player_X_pixel - i, cube->player_Y_pixel - j, color);
        }
    }
    int a = 60;
    double angle = cube->player_angle;
    while (a > 0)
    {
        int x = (int)(cube->player_X_pixel + cos(angle) * i);
        int y = (int)(cube->player_Y_pixel + sin(angle) * i);

        if (cube->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
            break;
        mlx_put_pixel(image, x, y, color);
        i++;
        a--;
    }
    
    double x_oriz = (int)(cube->player_X_pixel / TILE_SIZE + 1) * TILE_SIZE;
    // printf("x_oriz = %d\n", (int)(cube->player_X_pixel / TILE_SIZE));
    while (1)
    {
        double h = cube->player_X_pixel - x_oriz;
        double y_oriz = fabs(cube->player_Y_pixel - (tan(cube->player_angle) * h));
        if (y_oriz >= HEIGHT || y_oriz < 0)
            break;;
        // printf("y_oriz = %f\n", y_oriz);
        mlx_put_pixel(image, x_oriz, y_oriz, ft_pixel(0x00, 0xFF, 0x0F, 0xFF));
        if (cube->map[(int)(y_oriz / TILE_SIZE)][(int)(x_oriz / TILE_SIZE)] == '1' || cube->map[(int)(y_oriz / TILE_SIZE)][(int)((x_oriz - 4) / TILE_SIZE)] == '1')
            break;;
        x_oriz += TILE_SIZE;
    }
    double y_vert = (int)(cube->player_Y_pixel / TILE_SIZE) * TILE_SIZE;
    while (1)
    {
        double h = cube->player_Y_pixel - y_vert;
        printf("h = %f\n", h);
        double x_vert = fabs(cube->player_X_pixel - (h / tan(cube->player_angle)));
        if (x_vert >= HEIGHT || x_vert < 0) 
            return;
        printf("x_vert = %f\n", x_vert);
        mlx_put_pixel(image, x_vert, y_vert, ft_pixel(0x00, 0xFF, 0x0F, 0xFF));
        if (cube->map[(int)(y_vert / TILE_SIZE)][(int)(x_vert / TILE_SIZE)] == '1' || cube->map[(int)((y_vert - 4) / TILE_SIZE)][(int)(x_vert / TILE_SIZE)] == '1')
            return;
        y_vert -= TILE_SIZE;
    }
}


void ft_render_pixel(int32_t x, int32_t y, int32_t color, t_cube *cube)
{
    (void)cube;
    int i, j;
    i = 0;
    j = 0;
    while (i < TILE_SIZE - 2)
    {
        j = 0;
        while (j < TILE_SIZE - 2)
        {
            mlx_put_pixel(image, x * TILE_SIZE + i + 1, y * TILE_SIZE + j + 1, color);
            j++;
        }
        i++;
    }
}

void ft_randomize(void* param)
{
    t_cube* cube = (t_cube *)param;
    int x = 0;
    int y = 0;
    mlx_delete_image(cube->mlx, image);
    image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
    mlx_image_to_window(cube->mlx, image, 0, 0);

    while (cube->map[x])
    {
        y = 0;
        while (cube->map[x][y])
        {
            if (cube->map[x][y] == '1')
               ft_render_pixel( y, x, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF), cube); // White
            else if (cube->map[x][y] == '0' || cube->map[x][y] == ' ')
               ft_render_pixel( y, x, ft_pixel(0x00, 0x00, 0x00, 0xFF), cube); // Black
            else if (cube->map[x][y] == 'W')
                ft_render_pixel( y, x, ft_pixel(0x00, 0x00, 0x00, 0xFF), cube); // Black
            y++;
        }
        x++;
    }
    ft_render_pixel_player(ft_pixel(0xFF, 0x00, 0x00, 0xFF), cube); // Red
}

void ft_hook(void* param)
{
    t_cube *cube = (t_cube *)param;

    if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(cube->mlx);

    // Rotate player
    if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
    {
        cube->player_angle -= 0.04;
        if (cube->player_angle < 0)
            cube->player_angle += 2 * M_PI;
        // printf("angle = %f\n", cube->player_angle);
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
    {
        cube->player_angle += 0.04;
        cube->player_angle = fmod(cube->player_angle, 2 * M_PI);
    }
    
    double new_x = cube->player_X_pixel;
    double new_y = cube->player_Y_pixel;

    if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
    {
        new_x += cos(cube->player_angle) * 1; 
        new_y += sin(cube->player_angle) * 1;
        // printf("x %f\n", new_x);
        // printf("y %f\n", new_y);
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
    {
        new_x -= cos(cube->player_angle) * 1; 
        new_y -= sin(cube->player_angle) * 1; 
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
    {
        new_x -= cos(M_PI_2 + cube->player_angle) * 1;
        new_y -= sin(M_PI_2 + cube->player_angle) * 1;
        // printf("Ax %f\n", new_x);
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
    {
        new_x += cos(M_PI_2 + cube->player_angle) * 1;
        new_y += sin(M_PI_2 + cube->player_angle) * 1;
        // printf("Dx %f\n", new_x);
    }
    if (cube->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == '0' || cube->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == 'W')
    {
        cube->player_X_pixel = new_x;
        cube->player_Y_pixel = new_y;
    }

    ft_randomize(cube);
}


int main(int argc, char **argv)
{
    t_cube cube;

    is_map_valid(argc, argv, &cube);
    parse_textures(&cube, 0);
    parse_mape(&cube, NULL, NULL, 6);
    int a = parse_mape2(&cube);
    if (a == 1)                                              
        ft_error("Error : Map is invalid 2\n");

    cube.mlx = mlx_init((int32_t)WIDTH , (int32_t)HEIGHT, "MLX42", false);
    image = mlx_new_image(cube.mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	
    // cube.x_pixel = (float)WIDTH / (float)cube.width;
    // cube.y_pixel = (float)HEIGHT / (float)cube.height;
    // printf("x_pixel = %f\n", cube.x_pixel);
    // printf("y_pixel = %f\n", cube.y_pixel);
    get_player_position(&cube);
    
    cube.player_angle = 0;
    mlx_image_to_window(cube.mlx, image, 0, 0);
    ft_randomize(&cube);
    mlx_loop_hook(cube.mlx, ft_hook, &cube);
    mlx_loop(cube.mlx);
    return (EXIT_SUCCESS);
}