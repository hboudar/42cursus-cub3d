/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:26:08 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/01 11:07:22 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

double	small_distance(t_cube *cube, t_player *p, double d_or, double d_vr)
{
	int	tz;

	tz = TILE_SIZE;
	d_or = sqrt(pow(p->x - p->or_x, 2) + pow(p->y - p->or_y, 2));
	d_vr = sqrt(pow(p->x - p->vr_x, 2) + pow(p->y - p->vr_y, 2));
	if (d_or < d_vr)
	{
		cube->window.ray_intercept = p->or_x;
		if (cube->pars.map[(int)(p->or_y / tz)][(int)(p->or_x / tz)] == 'D')
			p->way = 'D';
		else if (p->facing_up)
			p->way = 'W';
		else if (p->facing_down)
			p->way = 'E';
		return (d_or);
	}
	cube->window.ray_intercept = p->vr_y;
	if (cube->pars.map[(int)(p->vr_y / tz)][(int)(p->vr_x / tz)] == 'D')
		p->way = 'D';
	else if (cube->player.facing_left)
		cube->player.way = 'N';
	else if (cube->player.facing_right)
		cube->player.way = 'S';
	return (d_vr);
}

static int	check_wall(double x, double y, t_cube *cube, t_win *window)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_x >= window->width
		|| map_y < 0 || map_y >= window->height)
		return (1);
	if ((int)ft_strlen(cube->pars.map[map_y]) <= map_x)
		return (1);
	if (cube->pars.map[map_y][map_x] == '1'
		|| cube->pars.map[map_y][map_x] == 'D')
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
		player->facing_right = (ray_angle < 0.5 * M_PI
				|| ray_angle > 1.5 * M_PI);
		player->facing_left = !player->facing_right;
		ray_angle = normalize_angle(ray_angle);
		get_oriz(cube, ray_angle, TILE_SIZE / tan(ray_angle), TILE_SIZE);
		get_vert(cube, ray_angle, TILE_SIZE, TILE_SIZE * tan(ray_angle));
		player->true_distance = small_distance(cube, player, 0, 0);
		cube->exec.ray_angle = ray_angle;
		cube->exec.ray = ray;
		if (ray == WIDTH / 2)
			cube->window.mid_ray_distance = player->true_distance;
		render_window(cube, &cube->exec, player, &cube->window);
		ray_angle += FOV / WIDTH;
		ray_angle = normalize_angle(ray_angle);
	}
}
