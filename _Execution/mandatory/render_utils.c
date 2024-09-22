/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:53:17 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/22 16:56:22 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	check_move(t_cube *cube, double move_x, double move_y)
{
	int	index_x;
	int	index_y;
	int	to_x;
	int	to_y;

	to_x = floor(cube->player.x + move_x) / TILE_SIZE;
	to_y = floor(cube->player.y + move_y) / TILE_SIZE;
	index_x = floor(cube->player.x) / TILE_SIZE;
	index_y = floor(cube->player.y) / TILE_SIZE;
	if (to_x < 0 || to_x >= cube->width || to_y < 0 || to_y >= cube->height)
		return ;
	if (cube->map[to_y][to_x] == '1')
		return ;
	else if (to_x != index_x && to_y != index_y)
	{
		if (cube->map[to_y][index_x] == '1' || cube->map[index_y][to_x] == '1')
			return ;
	}
	cube->player.x += move_x;
	cube->player.y += move_y;
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
