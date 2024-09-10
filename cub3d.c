/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/10 11:23:38 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_press(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
}

void	init_exec(t_cube *cube)
{
	cube->mlx = mlx_init((int32_t)WIDTH, (int32_t)HEIGHT, "MLX42", false);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
	mlx_loop_hook(cube->mlx, key_press, cube);
	// mlx_loop(cube->mlx);
	// get_player_position(cube);
	// cube->wall_1 = mlx_load_png(cube->textures.no);
	// cube->wall_2 = mlx_load_png(cube->textures.so);
	// cube->wall_3 = mlx_load_png(cube->textures.ea);
	// cube->wall_4 = mlx_load_png(cube->textures.we);
	// if (!cube->wall_1 || !cube->wall_2 || !cube->wall_3 || !cube->wall_4)
	// 	ft_error("Error : Texture not found\n");
	// (cube->player_init_dir == N) && (cube->player_angle = 0);
	// (cube->player_init_dir == S) && (cube->player_angle = M_PI);
	// (cube->player_init_dir == W) && (cube->player_angle = 3 * M_PI_2);
	// (cube->player_init_dir == E) && (cube->player_angle = M_PI_2);
	// cube->sprite_count = 0;
}

int	main(int argc, char *argv[])
{
	t_cube	cube;

	is_map_valid(argc, argv, &cube);
	init_exec(&cube);
	// mlx_loop_hook(cube.mlx, ft_randomize, &cube);
	// mlx_loop(cube.mlx);
	return (EXIT_SUCCESS);
}