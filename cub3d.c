/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/16 09:19:03 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_pixel_to_image(t_cube *cube, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE - 1)
	{
		j = 0;
		while (j < TILE_SIZE - 1)
		{
			// if (x == 0 || y == 0)
				mlx_put_pixel(cube->image, x + i, y + j, color);
			// else
				// mlx_put_pixel(cube->image, x + i - TILE_SIZE, y - TILE_SIZE + j, color);
			j++;
		}
		i++;
	}
}

void ft_randomize(void* param)
{
	int x;
	int y;
	t_cube* cube;
	uint32_t	color;

	y = 0;
	cube = (t_cube*)param;
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
	x = cube->player.y_map * TILE_SIZE + TILE_SIZE / 2;
	y = cube->player.x_map * TILE_SIZE + TILE_SIZE / 2;
	mlx_put_pixel(cube->image, x, y, ft_pixel(255, 0, 0, 255));
}

void	init_exec(t_cube *cube)
{
	cube->mlx = mlx_init((int32_t)WIDTH, (int32_t)HEIGHT, "MLX42", false);
	(!cube->mlx) && (ft_error("Error : MLX not found\n"));
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
		ft_error("Error : Image not found\n");
	(!cube->image) && ft_error("Error : Image not found\n");
	mlx_loop_hook(cube->mlx, ft_randomize, cube);
	mlx_loop(cube->mlx);
	// get_player_position(cube);
	// cube->wall_1 = mlx_load_png(cube->textures.no);
	// cube->wall_2 = mlx_load_png(cube->textures.so);
	// cube->wall_3 = mlx_load_png(cube->textures.ea);
	// cube->wall_4 = mlx_load_png(cube->textures.we);
	// if (!cube->wall_1 || !cube->wall_2 || !cube->wall_3 || !cube->wall_4)
	// 	ft_error("Error : Texture not found\n");
	// (cube->player_init_dir == N) && (cube->player_angle = 0);
	// (cube->player_init_dir == S) && (cube->player_angle = M_PI);
	// (cube->player_init_dir == W) && (cube->player_angle = 3 * M_PI_2);
	// (cube->player_init_dir == E) && (cube->player_angle = M_PI_2);
	// cube->sprite_count = 0;
}

int	main(int argc, char *argv[])
{
	t_cube	cube;

	is_map_valid(argc, argv, &cube);
	init_exec(&cube);
	return (EXIT_SUCCESS);
}
