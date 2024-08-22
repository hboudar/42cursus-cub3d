/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/22 17:23:33 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/syslimits.h>



// TODO: Implement this function again

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
    cube.texture = mlx_load_png("mario.png");
    if (!cube.texture)
        ft_error("Error : Texture not found\n");
    cube.player_angle = 3 * M_PI / 2;
    mlx_loop_hook(cube.mlx, ft_randomize, &cube);
    mlx_loop(cube.mlx);
    return (EXIT_SUCCESS);
}
