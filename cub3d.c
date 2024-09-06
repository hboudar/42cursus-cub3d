/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/06 15:56:01 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }
// void get_player_position(t_cube *cube)
// {
//     int x = 0;
//     int y = 0;
//     while (cube->map[x])
//     {
//         y = 0;
//         while (cube->map[x][y])
//         {
//             if (cube->map[x][y] == 'W')
//             {
//                 cube->player_X_pixel = y * cube->x_pixel + cube->x_pixel / 2;
//                 cube->player_Y_pixel = x * cube->y_pixel + cube->y_pixel / 2;
//                 cube->playerX = y;
//                 cube->playerY = x;
//                 return ;
//             }
//             y++;
//         }
//         x++;
//     }
// }
// void ft_render_pixel_player(int32_t color, t_cube *cube)
// {
//     int i, j;
//     for (i = 0; i < cube->x_pixel/5; i++)
//     {
//         for (j = 0; j < cube->y_pixel/11; j++)
//         {
//             mlx_put_pixel(image, cube->player_X_pixel - j, cube->player_Y_pixel - i, color);
//             mlx_put_pixel(image, cube->player_X_pixel + j, cube->player_Y_pixel + i, color);
//             mlx_put_pixel(image, cube->player_X_pixel - j, cube->player_Y_pixel + i, color);
//             mlx_put_pixel(image, cube->player_X_pixel + j, cube->player_Y_pixel - i, color);
//         }
//     }
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
//             // mlx_put_pixel(image, cube->player_X_pixel + j--, cube->player_Y_pixel + i++ , color);
// }
// void ft_render_pixel(int32_t x, int32_t y, int32_t color, t_cube *cube)
// {
//     int i, j;
//     for (i = 0; i < cube->x_pixel; i++)
//     {
//         for (j = 0; j < cube->y_pixel; j++)
//         {
//             mlx_put_pixel(image, x * cube->x_pixel + i, y * cube->y_pixel + j, color);
//         }
//     }
// }
// void ft_randomize(void* param)
// {
//     t_cube* cube = (t_cube *)param;
//     int x = 0;
//     int y = 0;
//     while (cube->map[x])
//     {
//         y = 0;
//         while (cube->map[x][y])
//         {
//             if (cube->map[x][y] == '1')
//                ft_render_pixel( y, x, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF), cube); // White
//             else if (cube->map[x][y] == '0' || cube->map[x][y] == ' ')
//                ft_render_pixel( y, x, ft_pixel(0x00, 0x00, 0x00, 0xFF), cube); // Black
//             else if (cube->map[x][y] == 'W')
//                 ft_render_pixel( y, x, ft_pixel(0x0, 0xF0, 0xD0, 0xFF), cube); // Turquoise
//             y++;
//         }
//         x++;
//     }
//     ft_render_pixel_player(ft_pixel(0xFF, 0x00, 0x00, 0xFF), cube); // Red
// }
// void ft_hook(void* param)
// {
//     t_cube *cube = (t_cube *)param;
//     if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
//         mlx_close_window(cube->mlx);
//     // int x_in_map = cube->playerX / cube->x_pixel;
//     // int y_in_map = cube->playerY / cube->y_pixel;
//     // // Calculate new player position
//     int new_x = cube->player_X_pixel;
//     int new_y = cube->player_Y_pixel;
//     if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
//         new_y -= 1; // Move left
//     if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
//         new_y += 1; // Move right
//     if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
//         new_x -= 1; // Move up
//     if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
//         new_x += 1; // Move down
//     // printf("%c\n", cube->map[(int)(new_y / cube->y_pixel)][(int)(new_x / cube->x_pixel)]);
//     if (cube->map[(int)(new_y  / cube->y_pixel)][(int)(new_x / cube->x_pixel)] == '0' || cube->map[(int)(new_y / cube->y_pixel)][(int)(new_x / cube->x_pixel)] == 'W')
//     {
//         cube->player_X_pixel = new_x;
//         cube->player_Y_pixel = new_y;
//     }
//     // Redraw the map and player
//     ft_randomize(cube);
// }

int main(int argc, char **argv)
{
    t_cube cube;

    is_map_valid(argc, argv, &cube);
    // cube.mlx = mlx_init((int32_t)WIDTH , (int32_t)HEIGHT, "MLX42", false);
    // image = mlx_new_image(cube.mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
    // cube.x_pixel = (float)WIDTH / (float)cube.width;
    // cube.y_pixel = (float)HEIGHT / (float)cube.height;
    // printf("x_pixel = %f\n", cube.x_pixel);
    // printf("y_pixel = %f\n", cube.y_pixel);
    // get_player_position(&cube);
    // cube.player_angle = 0;
    // // Calculate player's pixel position
    // mlx_image_to_window(cube.mlx, image, 0, 0);
    // ft_randomize(&cube);
    // mlx_loop_hook(cube.mlx, ft_hook, &cube);
    // mlx_loop(cube.mlx);
    return (EXIT_SUCCESS);
}

/*
    libft used :

    ft_putstr_fd
    ft_strlen
    ft_strjoin
    get_next_line
    ft_split
    ft_substr
    ft_strdup
    ft_memcpy
    ft_strncmp
    ft_strtrim
    ft_strchr 
*/
