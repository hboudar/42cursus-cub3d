/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/31 14:50:01 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdint.h>

static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_render_pixel(int32_t x, int32_t y, int32_t color)
{
    int i, j;
    for (i = 0; i < 45; i++)
    {
        for (j = 0; j < 45; j++)
        {
            mlx_put_pixel(image, x * 45 + i, y * 45 + j, color);
        }
    }
}


void ft_randomize(void* param)
{
    t_cube* cube = (t_cube *)param;
    int x = 0;
    int y = 0;
    while (cube->map[x])
    {
        y = 0;
        while (cube->map[x][y])
        {
            if (cube->map[x][y] == '1')
               ft_render_pixel( y, x, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF)); // White
            else if (cube->map[x][y] == '0' || cube->map[x][y] == ' ')
               ft_render_pixel( y, x, ft_pixel(0x00, 0x00, 0x00, 0xFF)); // Black
            else if (cube->map[x][y] == 'W')
                ft_render_pixel(y, x, ft_pixel(0xFF, 0x00, 0x00, 0xFF)); // Red

            y++;
        }
        x++;
    }
}

//what is white color : 0xFF0000FF

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}


int main(int argc, char **argv)
{
    t_cube cube;
    mlx_t* mlx;

    is_map_valid(argc, argv, &cube);
    parse_textures(&cube, 0);
    parse_mape(&cube, NULL, NULL, 6);
    int a = parse_mape2(&cube);
    if (a == 1)                                              
        ft_error("Error : Map is invalid 2\n");

    mlx = mlx_init(cube.width * 45 , cube.height * 45, "MLX42", true);
    image = mlx_new_image(mlx, cube.width * 45 , cube.height * 45);
	
    mlx_image_to_window(mlx, image, 0, 0);
    ft_randomize(&cube);
    mlx_loop_hook(mlx, ft_hook, mlx);
    mlx_loop(mlx);
    return (EXIT_SUCCESS);
}