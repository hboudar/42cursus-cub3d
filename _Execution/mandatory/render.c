/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:51 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/19 16:04:08 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_direction_line(t_cube *cube, int length, uint32_t color)
{
	int	x = cube->player.x;
	int	y = cube->player.y;
	int	x_end;
	int	y_end;

	// Calculate the endpoint of the line based on the player's angle
	x_end = x + cos(cube->player.rotation_angle) * length;
	y_end = y + sin(cube->player.rotation_angle) * length;

	// Drawing the line (simple Bresenham's line algorithm could be used here)
	int dx = abs(x_end - (int)x);
	int dy = abs(y_end - (int)y);
	int sx = x < x_end ? 1 : -1;
	int sy = y < y_end ? 1 : -1;
	int err = dx - dy;

	while ((int)x != x_end || (int)y != y_end)
	{
		mlx_put_pixel(cube->image, (int)x, (int)y, color);
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; x += sx; }
		if (e2 < dx) { err += dx; y += sy; }
	}
}

void	ft_pixel_to_image(t_cube *cube, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE - 1)
	{
		j = -1;
		while (++j < TILE_SIZE - 1)
			mlx_put_pixel(cube->image, x + i, y + j, color);
		i++;
	}
}

void	draw_circle(t_cube *cube, uint32_t color)
{
	int	x;
	int	y;

	y = -cube->player.radius;
	while (y <= cube->player.radius)
	{
		x = -cube->player.radius;
		while (x <= cube->player.radius)
		{
			if ((x * x) + (y * y)
				<= (cube->player.radius * cube->player.radius))
				mlx_put_pixel(cube->image, cube->player.x + x, cube->player.y + y, color);
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
	draw_circle(cube,ft_pixel(0, 255, 0, 255));
	draw_direction_line(cube, 50, ft_pixel(255, 0, 0, 255)); // Red line
}

int	check_move(t_cube *cube, double move_step_x, double move_step_y)
{
	int index_x;
	int index_y;
	int	x;
	int	y;

	x = floor(cube->player.x + move_step_x) / TILE_SIZE;
	y = floor(cube->player.y + move_step_y) / TILE_SIZE;
	index_x = floor(cube->player.x) / TILE_SIZE;
	index_y = floor(cube->player.y) / TILE_SIZE;
	if (x < 0 || x >= cube->width || y < 0 || y >= cube->height)
		return (0);
	if (cube->map[y][x] == '1')
		return (0);
	else if (x != index_x && y != index_y)
	{
		if (cube->map[y][index_x] == '1' || cube->map[index_y][x] == '1')
			return (0);
	}
	return (1);
}


void	hooks(t_cube *cube, t_player *player)
{
	double move_step_x = 0.0;
	double move_step_y = 0.0;

	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
	{
		move_step_x = cos(player->rotation_angle) * MOVE_SPEED;
		move_step_y = sin(player->rotation_angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
	{
		move_step_x = cos(player->rotation_angle) * -MOVE_SPEED;
		move_step_y = sin(player->rotation_angle) * -MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
	{
		move_step_x = -sin(player->rotation_angle) * MOVE_SPEED;
		move_step_y = cos(player->rotation_angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
	{
		move_step_x = sin(player->rotation_angle) * MOVE_SPEED;
		move_step_y = -cos(player->rotation_angle) * MOVE_SPEED;
	}
	if (check_move(cube, move_step_x, move_step_y))
	{
		player->x += move_step_x;
		player->y += move_step_y;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT)) // Rotate right
		player->rotation_angle += player->rotation_speed;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT)) // Rotate left
		player->rotation_angle -= player->rotation_speed;
}


void	mini_map(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	hooks(cube, &cube->player);
	render_map(cube);
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
		ft_error("Error : Image not found\n");
}
