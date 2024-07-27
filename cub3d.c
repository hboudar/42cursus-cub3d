/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/27 16:47:32 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    key_hook(int keycode, void *param)
{
	(void)param;
    if (keycode == 53)
        exit(0);
    return (0);
}

int	main(int argc, char **argv)
{
	t_cube	cube;

	is_map_valid(argc, argv, &cube);
	parse_textures(&cube, 0);
    // parse_mape(&cube);
	// cube.mlx = mlx_init();
	// cube.mlx_win = mlx_new_window(cube.mlx, 1920, 1080, "Hello world!");
    // mlx_key_hook(cube.mlx_win, key_hook, (void *)0);
	// mlx_loop(cube.mlx);
	
}
