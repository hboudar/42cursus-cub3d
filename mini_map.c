/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:18:43 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/22 17:00:21 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void background(mlx_image_t *image)
{
    int x = 0;
    int y = 0;
    while (y <  14 * 14)
    {
        x = 0;
        while (x < 16 * 20)
        {
            mlx_put_pixel(image, x, y,  ft_pixel(0xFF, 0x00, 0x00, 0xFF));
            x++;
        }
        y++;
    }
}

void ft_render_player(int32_t x, int32_t y, t_cube *cube, mlx_image_t *image)
{
    double i, j;
    i = 0;
    j = 0;
    while (i < 3)
    {
        j = 0;
        while (j < 3)
        {
            mlx_put_pixel(image, x * 14 + i + 6 + 1, y * 14 + j + 6 + 1, ft_pixel(0x00, 0xFF, 0x00, 0xFF));
             mlx_put_pixel(image, x * 14 - i + 6 + 1, y * 14 + j + 6 + 1, ft_pixel(0x00, 0xFF, 0x00, 0xFF));
                mlx_put_pixel(image, x * 14 + i + 6 + 1, y * 14 - j + 6 + 1, ft_pixel(0x00, 0xFF, 0x00, 0xFF));
                mlx_put_pixel(image, x * 14 - i + 6 + 1, y * 14 - j + 6 + 1, ft_pixel(0x00, 0xFF, 0x00, 0xFF));
                
            j++;
        }
        i++;
    }
}

void draw_mini_map(t_cube *cube, mlx_image_t *image)
{ 
    background(image);
    int player_tile_x = cube->playerX;
    int player_tile_y = cube->playerY;
    int start_x = player_tile_x - 5;
    int end_x = player_tile_x + 5;
    int start_y = player_tile_y - 5;
    int end_y = player_tile_y + 5;
    if (start_x < 0) start_x = 0;
    if (start_y < 0) start_y = 0;
    if (end_x > cube->columx) end_x = cube->columx;
    if (end_y > cube->columy) end_y = cube->columy;
    double fixed_player_x = 11;
    double fixed_player_y = 6; 
    while(start_y < end_y)
    {
        start_x = player_tile_x - 5;
        while(start_x < end_x)
        {
            if (cube->map[start_y][start_x] == '1')
                ft_render_pixel(start_x - player_tile_x + fixed_player_x, start_y - player_tile_y + fixed_player_y, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF), image); // White for walls
            else
                ft_render_pixel(start_x - player_tile_x + fixed_player_x, start_y - player_tile_y + fixed_player_y, ft_pixel(0xFF, 0x00, 0x00, 0xFF), image); 
            start_x++;
        }
        start_y++;
    }
    ft_render_player(fixed_player_x, fixed_player_y, cube, image);
    // printf("player pixel x: %f\n", cube->player_X_pixel);
    // printf("player pixel y: %f\n", cube->player_Y_pixel);
}
