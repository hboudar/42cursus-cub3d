/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:17:23 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/25 19:41:59 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void ft_mouse_hook(t_cube *cube)
{
    static int prev_mouseX = -1;
    static int prev_mouseY = -1;
    // if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_MIDDLE))
    // {
    //     (cube->textures.f[0]++ > 255) ? cube->textures.f[0] = 0 : 0;
    //     (cube->textures.f[1]++ > 255) ? cube->textures.f[1] = 0 : 0;
    //     (cube->textures.f[2]++ > 255) ? cube->textures.f[2] = 0 : 0;
    //     (cube->textures.f[3]++ > 255) ? cube->textures.f[3] = 0 : 0;
    //     (cube->textures.c[0]++ > 255) ? cube->textures.c[0] = 0 : 0;
    //     (cube->textures.c[1]++ > 255) ? cube->textures.c[1] = 0 : 0;
    //     (cube->textures.c[2]++ > 255) ? cube->textures.c[2] = 0 : 0;
    //     (cube->textures.c[3]++ > 255) ? cube->textures.c[3] = 0 : 0;
    // }
    if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT))
        mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_HIDDEN);

    if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_RIGHT))
        mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_NORMAL);
    mlx_get_mouse_pos(cube->mlx, &cube->mouseX, &cube->mouseY);
    if (prev_mouseX != -1 && prev_mouseY != -1) 
    {
        if (cube->mouseX != prev_mouseX || cube->mouseY != prev_mouseY) 
        {
            (cube->mouseX > prev_mouseX) && (cube->player_angle += ROTATION_SPEED);
            (cube->mouseX < prev_mouseX) && (cube->player_angle -= ROTATION_SPEED);
        }
    }
    (prev_mouseX = cube->mouseX, prev_mouseY = cube->mouseY);
}

void check_posssible_move(t_cube *cube, double new_x, double new_y)
{
    int map_x = (int)(new_x / TILE_SIZE);
    int map_y = (int)(new_y / TILE_SIZE);
    int map_x_left = (int)((new_x - 1) / TILE_SIZE);
    int map_x_right = (int)((new_x + 1) / TILE_SIZE);
    int map_y_up = (int)((new_y - 1) / TILE_SIZE);
    int map_y_down = (int)((new_y + 1) / TILE_SIZE);
    if (cube->map[map_y][map_x] == '0' || cube->map[map_y][map_x] == 'W')
    {
        if (cube->map[map_y_up][map_x] != '1' && 
            cube->map[map_y_down][map_x] != '1' && 
            cube->map[map_y][map_x_left] != '1' && 
            cube->map[map_y][map_x_right] != '1')
        {

            if (cube->map[map_y][map_x] == '0')
            {
                cube->map[map_y][map_x] = 'W';
                cube->map[(int)cube->playerY][(int)cube->playerX] = '0';
            }
            cube->player_X_pixel = new_x;
            cube->player_Y_pixel = new_y;
            cube->playerX = map_x;
            cube->playerY = map_y;
        }
    }
}

void ft_hook(void* param)
{
    t_cube *cube = (t_cube *)param;
    if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(cube->mlx);
    if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
        cube->player_angle -= ROTATION_SPEED;
    if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
        cube->player_angle += ROTATION_SPEED;
    double new_x = cube->player_X_pixel;
    double new_y = cube->player_Y_pixel;
    if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
    {
        new_x += cos(cube->player_angle) * SPEED; 
        new_y += sin(cube->player_angle) * SPEED;
    }
     if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
    {
        new_x -= cos(cube->player_angle) * SPEED; 
        new_y -= sin(cube->player_angle) * SPEED;
    }
     if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
    {
        new_x -= cos(M_PI_2 + cube->player_angle) * SPEED;
        new_y -= sin(M_PI_2 + cube->player_angle) * SPEED;
    }
     if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
    {
        new_x += cos(M_PI_2 + cube->player_angle) * SPEED;
        new_y += sin(M_PI_2 + cube->player_angle) * SPEED;
    }

    if (mlx_is_key_down(cube->mlx, MLX_KEY_UP))
    {
        if (cube->up + 7 <= 400)
            cube->up += 7;
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_DOWN))
    {
        if (cube->up - 7 >= -400)
            cube->up -= 7;
    }
    check_posssible_move(cube, new_x, new_y);
}

void rander_weapons(t_cube *cube, mlx_image_t *image)
{
    // Calculate the starting position for the weapon image so that it is centered
    uint32_t start_x = 500;
    uint32_t start_y = HEIGHT - cube->weapon->height;

    uint32_t weapon_x = 0;
    uint32_t weapon_y = 0;

    while (weapon_y < cube->weapon->height)
    {
        weapon_x = 0;
        while (weapon_x < cube->weapon->width)
        {
            int color = get_pixel(cube->weapon, weapon_x, weapon_y);
            uint8_t alpha = (color >> 24) & 0xFF;
            if (alpha != 0x00)
                mlx_put_pixel(image, start_x + weapon_x, start_y + weapon_y, color);

            weapon_x++;
        }
        weapon_y++;
    }   
}


void ft_randomize(void* param)
{
    t_cube* cube = (t_cube *)param;
    ft_hook(cube);
    ft_mouse_hook(cube);
    mlx_delete_image(cube->mlx, cube->image);
    cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
    ray_casting(cube, cube->image);
    // draw_mini_map(cube, cube->image);
    // rander_weapons(cube, cube->image);
    mlx_image_to_window(cube->mlx, cube->image, 0, 0);
}
