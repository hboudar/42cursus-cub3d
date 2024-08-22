/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:17:20 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/21 11:02:57 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_render_pixel(int32_t x, int32_t y, int32_t color, mlx_image_t *image)
{
    double i, j;
    i = 0;
    j = 0;
    while (i < 14 - 1)
    {
        j = 0;
        while (j < 14 - 1)
        {
            mlx_put_pixel(image, x * 14 + i + 1, y * 14 + j + 1, color);
            j++;
        }
        i++;
    }
}

void    draw_utils(t_cube *cube, mlx_image_t *image, double angle)
{
     int j = 0;
     while (j < cube->true_distance)
     {
         int x = cube->player_X_pixel + j * cos(angle);
         int y = cube->player_Y_pixel + j * sin(angle);
         if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
             break;
         mlx_put_pixel(image, x, y, ft_pixel(0xFF, 0x00, 0x00, 0xFF));
         j++;
     }
    
}


void rander_map(t_cube *cube, mlx_image_t *image)
{

    int x = 0;
    int y = 0;
     while (cube->map[x])
    {
        y = 0;
        while (cube->map[x][y])
        {
            if (cube->map[x][y] == '1')
               ft_render_pixel( y, x, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF), image); // White
            else if (cube->map[x][y] == '0' || cube->map[x][y] == ' ')
               ft_render_pixel( y, x, ft_pixel(0x00, 0x00, 0x00, 0xFF), image); // Black
            else if (cube->map[x][y] == 'W')
                ft_render_pixel( y, x, ft_pixel(0x00, 0x00, 0x00, 0xFF), image); // Black
            y++;
        }
        x++;
    }
    
}

