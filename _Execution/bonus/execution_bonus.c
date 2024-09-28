/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:37:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/28 15:20:39 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

// void	draw_line(t_cube *cube, int length, int curr_x, int curr_y)
// {
// 	int			x_end;
// 	int			y_end;
// 	int			sx;
// 	int			sy;
// 	int			err;
// 	int			dx;
// 	int			dy;
// 	x_end = curr_x + cos(cube->player.rotation_angle) * length;
// 	y_end = curr_y + sin(cube->player.rotation_angle) * length;
// 	dx = abs(x_end - curr_x);
// 	dy = abs(y_end - curr_y);
// 	(1) && (sx = -1, sy = -1, err = dx - dy);
// 	(curr_x < x_end) && (sx = 1);
// 	(curr_y < y_end) && (sy = 1);
// 	while (curr_x != x_end || curr_y != y_end)
// 	{
// 		mlx_put_pixel(cube->image, curr_x, curr_y,
// 			ft_pixel(rand() % 255, rand() % 255, rand() % 255, 255));
// 		int e2 = 2 * err;
// 		if (e2 > -dy) { err -= dy; curr_x += sx; }
// 		if (e2 < dx) { err += dx; curr_y += sy; }
// 	}
// }

// static void	draw_circle(mlx_image_t *image, t_player *player)
// {
// 	int			x;
// 	int			y;
// 	y = -player->radius;
// 	while (y <= player->radius)
// 	{
// 		x = -player->radius;
// 		while (x <= player->radius)
// 		{
// 			if ((x * x) + (y * y) <= (player->radius * player->radius))
// 				mlx_put_pixel(image, player->x + x, player->y + y,
// 				ft_pixel(rand() % 255, rand() % 255, rand() % 255, 255));
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	render_map(t_cube *cube, t_player *player, char **map)
// {
// 	uint32_t	color;
// 	int			x;
// 	int			y;
// 	y = 0;
// 	player->radius = 3;
//     while (map[y] != NULL)
// 	{
// 		x = 0;
// 		while (map[y][x] != '\0')
// 		{
// 			(map[y][x] != '1') && (color = ft_pixel(0, 0, 0, 255));
// 			(map[y][x] == '1') && (color = ft_pixel(255, 255, 255, 255));
// 			if (map[y][x] != ' ')
// 				ft_pixel_to_image(cube->image,
// 					x * TILE_SIZE, y * TILE_SIZE, color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	draw_circle(cube->image, player);
//     draw_line(cube, 8, player->x, player->y);
// }

void render_minimap(t_cube *cube, t_player *player)
{
	int			x;
	int			y;

	player->radius = 3;
	y = -player->radius;
	while (y <= player->radius)
	{
		x = -player->radius;
		while (x <= player->radius)
		{
			if ((x * x) + (y * y) <= (player->radius * player->radius))
				mlx_put_pixel(cube->image, player->x + x, player->y + y,
				ft_pixel(rand() % 255, rand() % 255, rand() % 255, 255));
			x++;
		}
		y++;
	}
}

void	execution(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	key_hooks(cube, &cube->player, 0.0, 0.0);
	// key_rotations(cube->mlx, &cube->player);
	// ray_casting(cube, &cube->player);
	// render_map(cube, &cube->player, cube->parsing.map);
	render_minimap(cube, &cube->player);
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
		ft_error("Error : Image not found\n");
}

void	init_exec(t_cube *cube, t_player *player)
{
	cube->mlx = mlx_init((int32_t)WIDTH, (int32_t)HEIGHT, "MLX42", false);
	if (!cube->mlx)
		ft_error("Error : MLX not found\n");
	player->x = (player->x * TILE_SIZE) + ((double)TILE_SIZE / 2);
	player->y = (player->y * TILE_SIZE) + ((double)TILE_SIZE / 2);
	(player->way == 'E') && (player->rotation_angle = 0);
	(player->way == 'S') && (player->rotation_angle = M_PI / 2);
	(player->way == 'W') && (player->rotation_angle = M_PI);
	(player->way == 'N') && (player->rotation_angle = 3 * M_PI / 2);
	cube->window.t1 = mlx_load_png(cube->window.no);
	cube->window.t2 = mlx_load_png(cube->window.so);
	cube->window.t3 = mlx_load_png(cube->window.ea);
	cube->window.t4 = mlx_load_png(cube->window.we);
	if (!cube->window.t1 || !cube->window.t2
		|| !cube->window.t3 || !cube->window.t4)
		ft_error("Error : Texture not found\n");
	mlx_loop_hook(cube->mlx, execution, cube);
	mlx_loop(cube->mlx);
}
