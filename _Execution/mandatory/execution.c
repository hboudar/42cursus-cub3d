/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:37:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/25 23:20:22 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	execution(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	key_hooks(cube, &cube->player, 0.0, 0.0);
	key_rotations(cube->mlx, &cube->player);
	render_map(cube, &cube->player, cube->parsing.map);
	ray_casting(cube, &cube->player);
	draw_line(cube, 35, cube->player.x, cube->player.y);
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
		ft_error("Error : Image not found\n");
}

void	init_exec(t_cube *cube, t_player *player)
{
	cube->mlx = mlx_init((int32_t)WIDTH, (int32_t)HEIGHT, "MLX42", false);
	(!cube->mlx) && (ft_error("Error : MLX not found\n"));
	(player->direction == 'E') && (player->rotation_angle = 0);
	(player->direction == 'S') && (player->rotation_angle = M_PI / 2);
	(player->direction == 'W') && (player->rotation_angle = M_PI);
	(player->direction == 'N') && (player->rotation_angle = 3 * M_PI / 2);
	player->x = (player->x * TILE_SIZE) + 30;
	player->y = (player->y * TILE_SIZE) + 30;
	cube->wall_1 = mlx_load_png(cube->window.no);
	cube->wall_2 = mlx_load_png(cube->window.so);
	cube->wall_3 = mlx_load_png(cube->window.ea);
	cube->wall_4 = mlx_load_png(cube->window.we);
	if (!cube->wall_1 || !cube->wall_2 || !cube->wall_3 || !cube->wall_4)
		ft_error("Error : Texture not found\n");
	mlx_loop_hook(cube->mlx, execution, cube);
	mlx_loop(cube->mlx);
}
