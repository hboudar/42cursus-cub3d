/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:26:08 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/01 17:47:00 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	get_oriz(t_cube *cube, double angle, double x_step, double y_step)
{
	double	y_intercept;
	double	x_intercept;

	y_intercept = floor(cube->player.y / TILE) * TILE;
	(cube->player.facing_down) && (y_intercept += TILE);
	x_intercept = cube->player.x + (y_intercept - cube->player.y) / tan(angle);
	(cube->player.facing_up) && (y_step *= -1);
	(cube->player.facing_right && x_step < 0) && (x_step *= -1);
	(cube->player.facing_left && x_step > 0) && (x_step *= -1);
	(cube->player.facing_up) && (y_intercept -= 0.0001);
	while (1)
	{
		if (check_wall(x_intercept, y_intercept, cube))
		{
			cube->player.or_x = x_intercept;
			cube->player.or_y = y_intercept;
			break ;
		}
		else
		{
			x_intercept += x_step;
			y_intercept += y_step;
		}
	}
}

static void	get_vert(t_cube *cube, double angle, double x_step, double y_step)
{
	double	x_intercept;
	double	y_intercept;

	x_intercept = floor(cube->player.x / TILE) * TILE;
	(cube->player.facing_right) && (x_intercept += TILE);
	y_intercept = cube->player.y + (x_intercept - cube->player.x) * tan(angle);
	(cube->player.facing_left) && (x_step *= -1);
	(cube->player.facing_down && y_step < 0) && (y_step *= -1);
	(cube->player.facing_up && y_step > 0) && (y_step *= -1);
	(cube->player.facing_left) && (x_intercept -= 0.0001);
	while (1)
	{
		if (check_wall(x_intercept, y_intercept, cube))
		{
			cube->player.vr_x = x_intercept;
			cube->player.vr_y = y_intercept;
			break ;
		}
		else
		{
			x_intercept += x_step;
			y_intercept += y_step;
		}
	}
}

double	cast_ray(t_cube *cube, t_player *player)
{
	double	angle;
	double	true_distance;

	angle = normalize_angle(player->rotation_angle);
	player->facing_down = (angle > 0 && angle < M_PI);
	player->facing_up = !player->facing_down;
	player->facing_right = (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
	player->facing_left = !player->facing_right;
	get_oriz(cube, angle, TILE / tan(angle), TILE);
	get_vert(cube, angle, TILE, TILE * tan(angle));
	true_distance = small_distance(cube, player, 0, 0);
	return (true_distance);
}

void	ray_casting(t_cube *cube, t_player *player)
{
	double	ray_angle;

	cube->exec.ray = -1;
	ray_angle = normalize_angle(cube->player.rotation_angle) - (FOV / 2);
	while (++cube->exec.ray < WIDTH)
	{
		player->facing_down = (ray_angle > 0 && ray_angle < M_PI);
		player->facing_up = !player->facing_down;
		player->facing_right = (ray_angle < 0.5 * M_PI
				|| ray_angle > 1.5 * M_PI);
		player->facing_left = !player->facing_right;
		ray_angle = normalize_angle(ray_angle);
		get_oriz(cube, ray_angle, TILE / tan(ray_angle), TILE);
		get_vert(cube, ray_angle, TILE, TILE * tan(ray_angle));
		player->true_distance = small_distance(cube, player, 0, 0);
		cube->exec.ray_angle = ray_angle;
		render_window(cube, &cube->exec, player, &cube->window);
		ray_angle += FOV / WIDTH;
		ray_angle = normalize_angle(ray_angle);
	}
}
