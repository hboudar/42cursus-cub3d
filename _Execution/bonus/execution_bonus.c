/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:37:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/06 14:59:45 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	sprite_animation(t_cube *cube, t_sprite *sprite)
{
	int	w;

	if (sprite->sprite_count == 0)
		sprite->sprite = mlx_load_png("textures/s1.png");
	else if (sprite->sprite_count == 3)
		sprite->sprite = mlx_load_png("textures/s2.png");
	else if (sprite->sprite_count == 6)
		sprite->sprite = mlx_load_png("textures/s3.png");
	else if (sprite->sprite_count == 9)
		sprite->sprite = mlx_load_png("textures/s4.png");
	else if (sprite->sprite_count == 12)
		sprite->sprite = mlx_load_png("textures/s5.png");
	else if (sprite->sprite_count == 15)
		sprite->sprite = mlx_load_png("textures/s6.png");
	sprite->sprite_count++;
	if (sprite->sprite_count == 18)
		sprite->sprite_count = 0;
	w = 0;
	while (w < 500)
	{
		draw_sprite(cube, sprite, w, 0);
		w += 100;
	}
}

void	weapon_shoot(t_cube *cube, t_win *win)
{
	static int	shooting = 0;

	if (mlx_is_key_down(cube->mlx, MLX_KEY_SPACE))
	{
		if (shooting == 0)
		{
			win->weapon = mlx_load_png("textures/2.png");
			shooting = 1;
		}
		else if (shooting == 1)
		{
			win->weapon = mlx_load_png("textures/3.png");
			shooting = 2;
		}
		else if (shooting == 2)
		{
			win->weapon = mlx_load_png("textures/1.png");
			shooting = 0;
		}
	}
	else
	{
		win->weapon = mlx_load_png("textures/1.png");
		shooting = 0;
	}
}

void	execution(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	key_hooks(cube, &cube->player, 0.0, 0.0);
	mouse_hook(cube, &cube->window);
	weapon_shoot(cube, &cube->window);
	key_rotations(cube->mlx, &cube->player);
	ray_casting(cube, &cube->player);
	render_weapons(cube->image, cube->window.weapon);
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
	cube->window.t1 = mlx_load_png(cube->window.no);
	cube->window.t2 = mlx_load_png(cube->window.so);
	cube->window.t3 = mlx_load_png(cube->window.ea);
	cube->window.t4 = mlx_load_png(cube->window.we);
	cube->window.door = mlx_load_png("textures/door.png");
	cube->window.sky = mlx_load_png("textures/sky.png");
	cube->window.weapon = mlx_load_png("textures/1.png");
	if (!cube->window.t1 || !cube->window.t2 || !cube->window.t3
		|| !cube->window.t4 || !cube->window.door || !cube->window.sky
		|| !cube->window.weapon)
		ft_error("Error : Texture not found\n");
	mlx_loop_hook(cube->mlx, execution, cube);
	mlx_loop(cube->mlx);
}
