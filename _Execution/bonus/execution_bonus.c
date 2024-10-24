/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:37:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/20 10:30:32 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	execution(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	key_hooks(cube, &cube->player, 0.0, 0.0);
	mouse_hook(cube, &cube->win);
	weapon_shoot(cube, &cube->win);
	key_rotations(cube->mlx, &cube->player);
	ray_casting(cube, &cube->player);
	render_weapons(cube->image, cube->win.weapon);
	sprite_animation(cube, &cube->sprite);
	minimap(cube, &cube->player, 0, 0);
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
		ft_error("Error : Image not found\n");
}

void	init_exec(t_cube *cube, t_player *player)
{
	cube->mlx = mlx_init((int32_t)WIDTH, (int32_t)HEIGHT, "MLX42", false);
	if (!cube->mlx)
		ft_error("Error : MLX not found\n");
	player->x = (player->x * TILE) + ((double)TILE / 2);
	player->y = (player->y * TILE) + ((double)TILE / 2);
	(player->way == 'E') && (player->rotation_angle = 0);
	(player->way == 'S') && (player->rotation_angle = M_PI / 2);
	(player->way == 'W') && (player->rotation_angle = M_PI);
	(player->way == 'N') && (player->rotation_angle = 3 * M_PI / 2);
	cube->win.t1 = mlx_load_png(cube->win.no);
	cube->win.t2 = mlx_load_png(cube->win.so);
	cube->win.t3 = mlx_load_png(cube->win.ea);
	cube->win.t4 = mlx_load_png(cube->win.we);
	cube->win.door = mlx_load_png("textures/door.png");
	cube->win.sky = mlx_load_png("textures/sky.png");
	cube->win.weapon2[0] = mlx_load_png("textures/1.png");
	cube->win.weapon2[1] = mlx_load_png("textures/2.png");
	cube->win.weapon2[2] = mlx_load_png("textures/3.png");
	if (!cube->win.t1 || !cube->win.t2 || !cube->win.t3 || !cube->win.t4
		|| !cube->win.door || !cube->win.sky || !cube->win.weapon2[0]
		|| !cube->win.weapon2[1] || !cube->win.weapon2[2])
		ft_error("Error : Texture not found\n");
	sprite_load(cube);
	mlx_loop_hook(cube->mlx, execution, cube);
	mlx_loop(cube->mlx);
}
