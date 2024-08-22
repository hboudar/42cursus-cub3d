/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:17:23 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/22 16:59:55 by aghounam         ###   ########.fr       */
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

void ft_hook(void* param)
{
    t_cube *cube = (t_cube *)param;
    if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(cube->mlx);
    if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
        cube->player_angle -= 0.02;
    if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
        cube->player_angle += 0.02;
    double new_x = cube->player_X_pixel;
    double new_y = cube->player_Y_pixel;

    // Update new_x and new_y based on key presses
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

void ft_randomize(void* param)
{
    t_cube* cube = (t_cube *)param;
    ft_hook(cube);
    mlx_delete_image(cube->mlx, cube->image);
    cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
    ray_casting(cube, cube->image);
    draw_mini_map(cube, cube->image);
    mlx_image_to_window(cube->mlx, cube->image, 0, 0);
}
