/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:26:08 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/24 15:54:06 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	smallest_distance(t_cube *cube)
{
	double	distance_oriz;
	double	distance_vert;

	distance_oriz = sqrt(pow(cube->player.x - cube->orizontal_position_x, 2)
			+ pow(cube->player.y - cube->orizontal_position_y, 2));
	distance_vert = sqrt(pow(cube->player.x - cube->vertical_position_x, 2)
			+ pow(cube->player.y - cube->vertical_position_y, 2));
	if (distance_oriz < distance_vert)
		return (distance_oriz);
	return (distance_vert);
}

static int	check_wall(double x, double y, t_cube *cube)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_x >= cube->width || map_y < 0 || map_y >= cube->height)
		return (1);
	if ((int)ft_strlen(cube->map[map_y]) <= map_x)
		return (1);
	if (cube->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

static void	get_oriz(t_cube *cube, double angle, double x_step, double y_step)
{
	double	y_intercept;
	double	x_intercept;

	y_intercept = floor(cube->player.y / TILE_SIZE) * TILE_SIZE;
	(cube->facing_down) && (y_intercept += TILE_SIZE);
	x_intercept = cube->player.x + (y_intercept - cube->player.y) / tan(angle);
	(cube->facing_up) && (y_step *= -1);
	(cube->facing_right && x_step < 0) && (x_step *= -1);
	(cube->facing_left && x_step > 0) && (x_step *= -1);
	(cube->facing_up) && (y_intercept -= 0.0001);
	while (1)
	{
		if (check_wall(x_intercept, y_intercept, cube))
		{
			cube->orizontal_position_x = x_intercept;
			cube->orizontal_position_y = y_intercept;
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

	x_intercept = floor(cube->player.x / TILE_SIZE) * TILE_SIZE;
	(cube->facing_right) && (x_intercept += TILE_SIZE);
	y_intercept = cube->player.y + (x_intercept - cube->player.x) * tan(angle);
	(cube->facing_left) && (x_step *= -1);
	(cube->facing_down && y_step < 0) && (y_step *= -1);
	(cube->facing_up && y_step > 0) && (y_step *= -1);
	(cube->facing_left) && (x_intercept -= 0.0001);
	while (1)
	{
		if (check_wall(x_intercept, y_intercept, cube))
		{
			cube->vertical_position_x = x_intercept;
			cube->vertical_position_y = y_intercept;
			break ;
		}
		else
		{
			x_intercept += x_step;
			y_intercept += y_step;
		}
	}
}

void	ray_casting(t_cube *cube)
{
	double	angle;
	int		ray;

	ray = -1;
	angle = normalize_angle(cube->player.rotation_angle) - (FOV / 2);
	while (++ray < WIDTH)
	{
		cube->facing_down = (angle > 0 && angle < M_PI) * 1;
		cube->facing_up = !cube->facing_down;
		cube->facing_right = (angle < (0.5 * M_PI) || angle > (1.5 * M_PI));
		cube->facing_left = !cube->facing_right;
		get_oriz(cube, angle, TILE_SIZE / tan(angle), TILE_SIZE);
		get_vert(cube, angle, TILE_SIZE, TILE_SIZE * tan(angle));
		cube->true_distance = smallest_distance(cube);
		draw_rays(cube, cube->image, angle);
		angle += FOV / WIDTH;
		angle = normalize_angle(angle);
	}
}
