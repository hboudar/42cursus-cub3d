/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:15:53 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/01 11:00:44 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_line(t_cube *cube, t_player *player, t_exec *exec)
{
	int	curr_x;
	int	curr_y;

	curr_x = 95;
	curr_y = 95;
	exec->x_end = curr_x + cos(player->rotation_angle) * 15;
	exec->y_end = curr_y + sin(player->rotation_angle) * 15;
	exec->dx = abs(exec->x_end - curr_x);
	exec->dy = abs(exec->y_end - curr_y);
	(1) && (exec->sx = -1, exec->sy = -1, exec->err = exec->dx - exec->dy);
	(curr_x < exec->x_end) && (exec->sx = 1);
	(curr_y < exec->y_end) && (exec->sy = 1);
	while (curr_x != exec->x_end || curr_y != exec->y_end)
	{
		mlx_put_pixel(cube->image, curr_x, curr_y,
			ft_pixel(rand() % 255, rand() % 255, rand() % 255, 255));
		exec->e2 = 2 * exec->err;
		(exec->e2 > -exec->dy) && (exec->err -= exec->dy, curr_x += exec->sx);
		(exec->e2 < exec->dx) && (exec->err += exec->dx, curr_y += exec->sy);
	}
}

void	draw_player(t_cube *cube, int radius, int x, int y)
{
	y = -radius - 1;
	while (++y <= radius)
	{
		x = -radius - 1;
		while (++x <= radius)
		{
			if ((x * x) + (y * y) <= (radius * radius))
				mlx_put_pixel(cube->image,
					95 + x, 95 + y, ft_pixel(255, 20, 0, 180));
		}
	}
	y = -3;
	while (++y <= 2)
	{
		x = -3;
		while (++x <= 2)
		{
			if ((x * x) + (y * y) <= 9 && x <= 0 && y <= 0)
				mlx_put_pixel(cube->image, 95 + x, 95 + y,
					ft_pixel(255, 255, 255, 255));
			else if ((x * x) + (y * y) <= 9)
				mlx_put_pixel(cube->image, 95 + x, 95 + y,
					ft_pixel(0, 0, 0, 255));
		}
	}
}

int	is_a_wall(t_cube *cube, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor((cube->player.x + x) / TILE_SIZE);
	map_y = (int)floor((cube->player.y + y) / TILE_SIZE);
	if (map_x < 0 || map_x >= cube->window.width
		|| map_y < 0 || map_y >= cube->window.height)
		return (1);
	return ((cube->pars.map[map_y][map_x] == '1')
			+ (cube->pars.map[map_y][map_x] == 'D') * 2);
}

void	draw_mini_map(t_cube *cube, t_player *player, double x, double y)
{
	int	i;

	(1) && (player->radius = 77, y = -player->radius - 1);
	while (++y <= player->radius)
	{
		x = -player->radius - 1;
		while (++x <= player->radius)
		{
			if ((x * x) + (y * y) <= (player->radius * player->radius))
			{
				i = is_a_wall(cube, x, y);
				if (i == 1)
					mlx_put_pixel(cube->image,
						95 + x, 95 + y, ft_pixel(255, 255, 10, 200));
				else if (i == 2)
					mlx_put_pixel(cube->image,
						95 + x, 95 + y, ft_pixel(255, 0, 0, 255));
				else
					mlx_put_pixel(cube->image,
						95 + x, 95 + y, ft_pixel(0, 0, 0, 255));
			}
		}
	}
	draw_player(cube, 4, 0, 0);
	draw_line(cube, &cube->player, &cube->exec);
}

void	minimap_backround(t_cube *cube, t_player *player, double x, double y)
{
	int32_t	color;

	(1) && (player->radius = 80, y = -player->radius - 1);
	while (++y <= player->radius)
	{
		x = -player->radius - 1;
		while (++x <= player->radius)
		{
			if ((x * x) + (y * y) <= (player->radius * player->radius))
				mlx_put_pixel(cube->image,
					95 + x, 95 + y, ft_pixel(255, 0, 0, 255));
		}
	}
	draw_mini_map(cube, player, 0, 0);
	(1) && (x = -1, color = ft_pixel(255, 255, 255, 255));
	while (++x < 10)
	{
		mlx_put_pixel(cube->image, 95 - 4, 15 + x, color);
		mlx_put_pixel(cube->image, 95 - 5, 15 + x, color);
		mlx_put_pixel(cube->image, 95 + 5, 15 + x, color);
		mlx_put_pixel(cube->image, 95 + 6, 15 + x, color);
		mlx_put_pixel(cube->image, 95 - 4 + x, 15 + x, color);
		mlx_put_pixel(cube->image, 95 - 3 + x, 15 + x, color);
	}
}
