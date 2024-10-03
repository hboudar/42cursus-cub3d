/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:53:17 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/03 14:55:18 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

void	ft_pixel_to_image(mlx_image_t *image, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE - 1)
	{
		j = -1;
		while (++j < TILE - 1)
			mlx_put_pixel(image, x + i, y + j, color);
		i++;
	}
}

double	small_distance(t_cube *cube, t_player *p, double d_or, double d_vr)
{
	d_or = sqrt(pow(p->x - p->or_x, 2) + pow(p->y - p->or_y, 2));
	d_vr = sqrt(pow(p->x - p->vr_x, 2) + pow(p->y - p->vr_y, 2));
	if (d_or < d_vr)
	{
		(1) && (cube->window.y_ray = p->or_y, cube->window.x_ray = p->or_x);
		cube->window.ray_intercept = p->or_x;
		if (cube->pars.map[(int)(p->or_y / TILE)][(int)(p->or_x / TILE)] == 'C')
			p->way = 'C';
		else if (p->facing_up)
			p->way = 'W';
		else if (p->facing_down)
			p->way = 'E';
		return (d_or);
	}
	cube->window.ray_intercept = p->vr_y;
	if (cube->pars.map[(int)(p->vr_y / TILE)][(int)(p->vr_x / TILE)] == 'C')
		p->way = 'C';
	else if (cube->player.facing_left)
		cube->player.way = 'N';
	else if (cube->player.facing_right)
		cube->player.way = 'S';
	(1) && (cube->window.y_ray = p->vr_y, cube->window.x_ray = p->vr_x);
	return (d_vr);
}

int	check_wall(double x, double y, t_cube *cube)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE);
	map_y = floor(y / TILE);
	if (map_x < 0 || map_x >= cube->window.width
		|| map_y < 0 || map_y >= cube->window.height)
		return (1);
	if ((int)ft_strlen(cube->pars.map[map_y]) <= map_x)
		return (1);
	if (cube->exec.mode && cube->pars.map[map_y][map_x] == 'O')
	{
		cube->window.door_state = 1;
		cube->window.mid_ray_distance = sqrt(pow(cube->player.x - x, 2)
				+ pow(cube->player.y - y, 2));
		if (cube->window.mid_ray_distance < TILE * 1.5)
			cube->pars.map[map_y][map_x] = 'C';
		return (1);
	}
	if (cube->pars.map[map_y][map_x] == '1'
		|| cube->pars.map[map_y][map_x] == 'C')
		return (1);
	return (0);
}
