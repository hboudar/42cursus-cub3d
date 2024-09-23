/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:37:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/23 10:20:34 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*

void	raycasting(t_cube *cube, t_player *player)
{
	
}

*/

void	rotations(void *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->rotation_angle += player->rotation_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->rotation_angle -= player->rotation_speed;
}

void	hooks(t_cube *cube, t_player *player, double move_x, double move_y)
{
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
	{
		move_x = cos(player->rotation_angle) * MOVE_SPEED;
		move_y = sin(player->rotation_angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
	{
		move_x = cos(player->rotation_angle) * -MOVE_SPEED;
		move_y = sin(player->rotation_angle) * -MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
	{
		move_x = -sin(player->rotation_angle) * MOVE_SPEED;
		move_y = cos(player->rotation_angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
	{
		move_x = sin(player->rotation_angle) * MOVE_SPEED;
		move_y = -cos(player->rotation_angle) * MOVE_SPEED;
	}
	check_move(cube, move_x, move_y);
}

void	execution(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	hooks(cube, &cube->player, 0.0, 0.0);
	rotations(cube->mlx, &cube->player);
	render_map(cube, &cube->player, cube->map);
	//raycasting(cube, &cube->player);
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
		ft_error("Error : Image not found\n");
}
