/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:51 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/19 08:49:58 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	draw_circle(t_cube *cube, int xc, int yc, uint32_t color)
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
				mlx_put_pixel(cube->image, xc + x, yc + y, color);
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
	x = cube->player.x * TILE_SIZE + TILE_SIZE / 2;
	y = cube->player.y * TILE_SIZE + TILE_SIZE / 2;
	draw_circle(cube, x, y, ft_pixel(0, 255, 0, 255));
}

void	hooks(void *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		player->walk_direction = 1;
	else if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player->walk_direction = -1;
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->turn_direction = 1;
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->turn_direction = -1;
}

void	mini_map(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	hooks(cube->mlx, &cube->player);
	render_map(cube);
}
