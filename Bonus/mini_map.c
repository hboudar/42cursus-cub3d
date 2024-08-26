/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:18:43 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/24 16:25:01 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void background(mlx_image_t *image)
{
    int radius = HEIGHT_MINI / 2; // Assuming the mini-map is square
    int centerX = WIDRH_MINI / 2;
    int centerY = HEIGHT_MINI / 2;

    for (int y = 0; y < HEIGHT_MINI; y++)
    {
        for (int x = 0; x < WIDRH_MINI; x++)
        {
            int dx = x - centerX;
            int dy = y - centerY;
            if (dx * dx + dy * dy <= radius * radius)
            {
                mlx_put_pixel(image, x, y, ft_pixel(0x80, 0x00, 0x00, 0xFF));
            }
        }
    }
}


void ft_render_player(int32_t x, int32_t y, t_cube *cube, mlx_image_t *image)
{
    double i, j;
    i = 0;
    j = 0;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            mlx_put_pixel(image, x * 14 + i + 6 + 1, y * 14 + j + 6 + 1, ft_pixel(0x00, 0xFF, 0x00, 0xFF));
             mlx_put_pixel(image, x * 14 - i + 6 + 1, y * 14 + j + 6 + 1, ft_pixel(0x00, 0xFF, 0x00, 0xFF));
                mlx_put_pixel(image, x * 14 + i + 6 + 1, y * 14 - j + 6 + 1, ft_pixel(0x00, 0xFF, 0x00, 0xFF));
                mlx_put_pixel(image, x * 14 - i + 6 + 1, y * 14 - j + 6 + 1, ft_pixel(0x00, 0xFF, 0x00, 0xFF));
                
            j++;
        }
        i++;
    }

    i = 0;
    while(i < 10)
    {
        int ray_x = cos(cube->player_angle) * i + 14 * x;
        int ray_y = sin(cube->player_angle) * i + 14 * y;
        mlx_put_pixel(image, ray_x + 7, ray_y + 7, ft_pixel(0x00, 0xFF, 0x00, 0xFF));
        i++;
    }
}

void draw_mini_map(t_cube *cube, mlx_image_t *image)
{ 
    // background(image);
    int player_tile_x = cube->playerX;
    int player_tile_y = cube->playerY;
    int start_x = player_tile_x - 7;
    int end_x = player_tile_x + 8;
    int start_y = player_tile_y - 5;
    int end_y = player_tile_y + 5;
    if (start_x < 0) start_x = 0;
    if (start_y < 0) start_y = 0;
    if (end_x > cube->columx) end_x = cube->columx;
    if (end_y > cube->columy) end_y = cube->columy;
    double fixed_player_x = 9;
    double fixed_player_y = 7; 
    while(start_y < end_y)
    {
        start_x = player_tile_x - 7;
        if (start_x < 0) start_x = 0;
        end_x = player_tile_x + 8;
        if (end_x > cube->columx) end_x = cube->columx;
        while(start_x < end_x)
        {
            if (!cube->map[start_y][start_x] || cube->map[start_y][start_x] != '1')
            {
                if (!cube->map[start_y][start_x])
                    break;
                ft_render_pixel(start_x - player_tile_x + fixed_player_x, start_y - player_tile_y + fixed_player_y, ft_pixel(0x80, 0x00, 0x00, 0xFF), image); // Red for empty spaces
            }
            else if (cube->map[start_y][start_x] == '1')
                ft_render_pixel(start_x - player_tile_x + fixed_player_x, start_y - player_tile_y + fixed_player_y, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF), image); // White for walls
            start_x++;
        }
        start_y++;
        if (start_y > cube->columy)
            break;
    }
    ft_render_player(fixed_player_x, fixed_player_y, cube, image);
}
