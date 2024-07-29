/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/29 15:14:01 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>

static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	main(int argc, char **argv)
{
	t_cube	cube;

	is_map_valid(argc, argv, &cube);
	parse_textures(&cube, 0);
	parse_mape(&cube, NULL, NULL, 6);
	int a = parse_mape2(&cube);
	if (a == 1)                                              
		ft_error("Error : Map is invalid 2\n");
	else
	 	printf("Map is valid\n");
	if (!(cube.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(cube.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(cube.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop(cube.mlx);
	mlx_terminate(cube.mlx);
	return (EXIT_SUCCESS);
}
