/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:51 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/22 17:00:34 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_line(t_cube *cube, int length, int curr_x, int curr_y)
{
	uint32_t	color;
	int	x_end;
	int	y_end;
	int	sx;
	int	sy;
	int err;

	color = ft_pixel(255, 255, 0, 255);
	x_end = curr_x + cos(cube->player.rotation_angle) * length;
	y_end = curr_y + sin(cube->player.rotation_angle) * length;
	int dx = abs(x_end - curr_x);
	int dy = abs(y_end - curr_y);
	(1) && (sx = -1, sy = -1, err = dx - dy);

	(curr_x < x_end) && (sx = 1);
	(curr_y < y_end) && (sy = 1);

	while (curr_x != x_end || curr_y != y_end)
	{
		mlx_put_pixel(cube->image, curr_x, curr_y, color);
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; curr_x += sx; }
		if (e2 < dx) { err += dx; curr_y += sy; }
	}
}

static void	draw_circle(mlx_image_t *image, t_player *player)
{
	uint32_t	color;
	int			x;
	int			y;

	color = ft_pixel(255, 0, 0, 255);
	y = -player->radius;
	while (y <= player->radius)
	{
		x = -player->radius;
		while (x <= player->radius)
		{
			if ((x * x) + (y * y)
				<= (player->radius * player->radius))
				mlx_put_pixel(image, player->x + x, player->y + y, color);
			x++;
		}
		y++;
	}
}

void	render_map(void *param)
{
	t_cube		*cube;
	uint32_t	color;
	int			x;
	int			y;

	y = 0;
	cube = (t_cube *)param;
	while (cube->map[y] != NULL)
	{
		x = 0;
		while (cube->map[y][x] != '\0')
		{
			(cube->map[y][x] != '1') && (color = ft_pixel(0, 0, 0, 255));
			(cube->map[y][x] == '1') && (color = ft_pixel(255, 255, 255, 255));
			if (cube->map[y][x] != ' ')
				ft_pixel_to_image(cube, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	draw_circle(cube->image, &cube->player);
	draw_line(cube, 50, cube->player.x, cube->player.y);
}
