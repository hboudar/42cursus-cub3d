/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/22 16:59:31 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_exec(t_cube *cube, t_player *player)
{
	cube->mlx = mlx_init((int32_t)WIDTH, (int32_t)HEIGHT, "MLX42", false);
	(!cube->mlx) && (ft_error("Error : MLX not found\n"));
	(player->player == 'E') && (player->rotation_angle = 0);
	(player->player == 'S') && (player->rotation_angle = M_PI / 2);
	(player->player == 'W') && (player->rotation_angle = M_PI);
	(player->player == 'N') && (player->rotation_angle = 3 * M_PI / 2);
	player->rotation_speed = ROTATION_SPEED * (M_PI / 180);
	player->x = (player->x * TILE_SIZE) + (TILE_SIZE / 2);
	player->y = (player->y * TILE_SIZE) + (TILE_SIZE / 2);
	mlx_loop_hook(cube->mlx, execution, cube);
	mlx_loop(cube->mlx);
}

int	main(int argc, char *argv[])
{
	t_cube	cube;

	is_map_valid(argc, argv, &cube);
	init_exec(&cube, &cube.player);
	return (EXIT_SUCCESS);
}
