/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/26 18:50:03 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/syslimits.h>


mlx_mousefunc ft_mouse(void* param)
{
    t_cube *cube = (t_cube *)param;
    if (!cube) 
    {
        printf("Invalid cube or mlx pointer\n");
        return (0);
    }

    mlx_get_mouse_pos(cube->mlx, &cube->mouseX, &cube->mouseY);

    if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT))
    {
        mlx_set_cursor_mode(cube->mlx, false);
    }
    if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_RIGHT))
    {
        mlx_set_cursor_mode(cube->mlx, true);
    }
    
    // Uncomment this code after verifying no segmentation fault occurs
    // if ((cube->mouseX > WIDTH / 2 + WIDTH / 4) && (cube->mouseY > HEIGHT / 2 && cube->mouseY < HEIGHT))
    //     cube->player_angle += 0.01;
    // if (cube->mouseX < WIDTH / 4 && (cube->mouseY > HEIGHT / 2 && cube->mouseY < HEIGHT))
    //     cube->player_angle -= 0.01;
    
    return (0);
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
    cube.image = mlx_new_image(cube.mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
    get_player_position(&cube);
    cube.wall_1 = mlx_load_png(cube.textures.no);
    cube.wall_2 = mlx_load_png(cube.textures.so);
    cube.wall_3 = mlx_load_png(cube.textures.ea);
    cube.wall_4 = mlx_load_png(cube.textures.we);
    cube.weapon = mlx_load_png("1.png");
    cube.door = mlx_load_png("door1.png");
    if (!cube.wall_1 || !cube.wall_2 || !cube.weapon || !cube.wall_3 || !cube.wall_4)
        ft_error("Error : Texture not found\n");
    (cube.player_init_dir == N) && (cube.player_angle = 0);
    (cube.player_init_dir == S) && (cube.player_angle = M_PI);
    (cube.player_init_dir == W) && (cube.player_angle = 3 * M_PI_2);
    (cube.player_init_dir == E) && (cube.player_angle = M_PI_2);
    cube.up = 0;
    cube.weapon_pos = 0;
    cube.flag_door = 0;
    mlx_loop_hook(cube.mlx, ft_randomize, &cube);
    // mlx_mouse_hook(cube.mlx, (mlx_mousefunc)ft_mouse, &cube);
    mlx_loop(cube.mlx);
    return (EXIT_SUCCESS);
}

// TODO : work for the next day

// 1. Wall collisions.
// 2. texture rendering.
// 3. 