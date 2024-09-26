/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:26:08 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/25 23:25:31 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	smallest_distance(t_cube *cube)
{
	double	distance_oriz;
	double	distance_vert;

	distance_oriz = sqrt(pow(cube->player.x - cube->player.orizontal_x, 2)
			+ pow(cube->player.y - cube->player.orizontal_y, 2));
	distance_vert = sqrt(pow(cube->player.x - cube->player.vertical_x, 2)
			+ pow(cube->player.y - cube->player.vertical_y, 2));
	if (distance_oriz < distance_vert)
	{
		// cube->ray_intercept = cube->player.orizontal_x;
        // if (cube->player.facing_up)
        //     cube->player.direction = 'W';
        // else if (cube->player.facing_down)
        //     cube->player.direction = 'E';
		return (distance_oriz);
	}
	// cube->ray_intercept = cube->player.vertical_y;
    // if (cube->player.facing_left)
    //     cube->player.direction = 'N';
    // else if (cube->player.facing_right)
    //     cube->player.direction = 'S';
	return (distance_vert);
}

static int	check_wall(double x, double y, t_cube *cube, t_window *window)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_x >= window->width || map_y < 0 || map_y >= window->height)
		return (1);
	if ((int)ft_strlen(cube->parsing.map[map_y]) <= map_x)
		return (1);
	if (cube->parsing.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

static void	get_oriz(t_cube *cube, double angle, double x_step, double y_step)
{
	double	y_intercept;
	double	x_intercept;

	y_intercept = floor(cube->player.y / TILE_SIZE) * TILE_SIZE;
	(cube->player.facing_down) && (y_intercept += TILE_SIZE);
	x_intercept = cube->player.x + (y_intercept - cube->player.y) / tan(angle);
	(cube->player.facing_up) && (y_step *= -1);
	(cube->player.facing_right && x_step < 0) && (x_step *= -1);
	(cube->player.facing_left && x_step > 0) && (x_step *= -1);
	(cube->player.facing_up) && (y_intercept -= 0.0001);
	while (1)
	{
		if (check_wall(x_intercept, y_intercept, cube, &cube->window))
		{
			cube->player.orizontal_x = x_intercept;
			cube->player.orizontal_y = y_intercept;
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
	(cube->player.facing_right) && (x_intercept += TILE_SIZE);
	y_intercept = cube->player.y + (x_intercept - cube->player.x) * tan(angle);
	(cube->player.facing_left) && (x_step *= -1);
	(cube->player.facing_down && y_step < 0) && (y_step *= -1);
	(cube->player.facing_up && y_step > 0) && (y_step *= -1);
	(cube->player.facing_left) && (x_intercept -= 0.0001);
	while (1)
	{
		if (check_wall(x_intercept, y_intercept, cube, &cube->window))
		{
			cube->player.vertical_x = x_intercept;
			cube->player.vertical_y = y_intercept;
			break ;
		}
		else
		{
			x_intercept += x_step;
			y_intercept += y_step;
		}
	}
}

void	ray_casting(t_cube *cube, t_player *player)
{
	double	ray_angle;
	int		ray;

	ray = -1;
	ray_angle = normalize_angle(cube->player.rotation_angle) - (FOV / 2);
	while (++ray < WIDTH)
	{
		player->facing_down = (ray_angle > 0 && ray_angle < M_PI);
		player->facing_up = !player->facing_down;
		player->facing_right = (ray_angle < (0.5 * M_PI) || ray_angle > (1.5 * M_PI));
		player->facing_left = !player->facing_right;
		get_oriz(cube, ray_angle, TILE_SIZE / tan(ray_angle), TILE_SIZE);
		get_vert(cube, ray_angle, TILE_SIZE, TILE_SIZE * tan(ray_angle));
		player->true_distance = smallest_distance(cube);
		draw_rays(cube, cube->image, ray_angle);
		// render_wall(cube, cube->image, ray_angle, player->true_distance);
		ray_angle += FOV / WIDTH;
		ray_angle = normalize_angle(ray_angle);
	}
}
