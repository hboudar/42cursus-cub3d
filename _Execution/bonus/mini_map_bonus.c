/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:15:53 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/30 11:54:47 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_line(t_cube *cube, int length, int curr_x, int curr_y)
{
	int			x_end;
	int			y_end;
	int			sx;
	int			sy;
	int			err;
	int			dx;
	int			dy;

	x_end = curr_x + cos(cube->player.rotation_angle) * length;
	y_end = curr_y + sin(cube->player.rotation_angle) * length;
	dx = abs(x_end - curr_x);
	dy = abs(y_end - curr_y);
	(1) && (sx = -1, sy = -1, err = dx - dy);
	(curr_x < x_end) && (sx = 1);
	(curr_y < y_end) && (sy = 1);
	while (curr_x != x_end || curr_y != y_end)
	{
		mlx_put_pixel(cube->image, curr_x, curr_y,
			ft_pixel(rand() % 255, rand() % 255, rand() % 255, 255));
		int e2 = 2 * err;
		(e2 > -dy) && (err -= dy, curr_x += sx);
		(e2 < dx) && (err += dx, curr_y += sy);
	}
}

void draw_player(t_cube *cube, int radius)
{
    int x;
    int y;

    y = -radius - 1;
    while (++y <= radius) // Loop through the bounding box of the circle
    {
        x = -radius - 1;
        while (++x <= radius)
        {
            if ((x * x) + (y * y) <= (radius * radius))// Check if the point (x, y) is inside the circle
                mlx_put_pixel(cube->image,
                    90 + x, 90 + y, ft_pixel(0, 255, 0, 255));
        }
    }
    draw_line(cube, 15, 90, 90);
}

void	draw_mini_map(t_cube *cube)
{
	
}

void minimap_backround(t_cube *cube, t_player *player, double x, double y)
{
	(1) && (player->radius = 65, y = -player->radius - 1);
	while (++y <= player->radius)
	{
		x = -player->radius - 1;
		while (++x <= player->radius)
		{
			if ((x * x) + (y * y) <= (player->radius * player->radius))
				mlx_put_pixel(cube->image,
                90 + x, 90 + y,ft_pixel(255, 255, 255, 255));
		}
	}
	(1) && (player->radius = 62, y = -player->radius - 1);
	while (++y <= player->radius)
	{
		x = -player->radius - 1;
		while (++x <= player->radius)
		{
			if ((x * x) + (y * y) <= (player->radius * player->radius))
				mlx_put_pixel(cube->image,
                90 + x, 90 + y,ft_pixel(0, 0, 0, 255));
		}
	}
	draw_mini_map(cube);
    draw_player(cube, 3);
}
