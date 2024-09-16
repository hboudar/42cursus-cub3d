/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:51 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/16 17:42:17 by hboudar          ###   ########.fr       */
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

void	render_map(void	*param)
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
	y = cube->player.y * TILE_SIZE + TILE_SIZE / 2;
	x = cube->player.x * TILE_SIZE + TILE_SIZE / 2;
	mlx_put_pixel(cube->image, x, y, ft_pixel(255, 0, 0, 255));
}

void	hooks(t_cube *cube)
{
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cube->mlx);
		exit(EXIT_SUCCESS);
	}
}

void	mini_map(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	hooks(cube);
	render_map(cube);
}
/*
else if (mlx_is_key_down(cube->mlx, MLX_KEY_UP))
{
	if (cube->map[cube->player.y - 1][cube->player.x] == '1')
		return ;
	cube->map[cube->player.y][cube->player.x] = '0';
	cube->map[cube->player.y - 1][cube->player.x] = 'W';
	cube->player.y--;
}
else if (mlx_is_key_down(cube->mlx, MLX_KEY_DOWN))
{
	if (cube->map[cube->player.y + 1][cube->player.x] == '1')
		return ;
	cube->map[cube->player.y][cube->player.x] = '0';
	cube->map[cube->player.y + 1][cube->player.x] = 'W';
	cube->player.y++;
}
else if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
{
	if (cube->map[cube->player.y][cube->player.x - 1] == '1')
		return ;
	cube->map[cube->player.y][cube->player.x] = '0';
	cube->map[cube->player.y][cube->player.x - 1] = 'W';
	cube->player.x--;
}
else if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
{
	if (cube->map[cube->player.y][cube->player.x + 1] == '1')
		return ;
	cube->map[cube->player.y][cube->player.x] = '0';
	cube->map[cube->player.y][cube->player.x + 1] = 'W';
	cube->player.x++;
}*/