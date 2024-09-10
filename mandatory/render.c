/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:51 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/10 15:25:19 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void render_map(t_cube *cube)
{
    int x;
    int y;

    y = 0;
    while (cube->map[y])
    {
        printf("[%s]\n", cube->map[y]);
        x = 0;
        // while (cube->map[y][x])
        // {
        //     printf("[%c]", cube->map[y][x]);
        //     if (cube->map[y][x] == '1')
        //         mlx_image_to_window(cube->mlx, cube->image, x, y);
        //     else if (cube->map[y][x] == '0')
        //         mlx_image_to_window(cube->mlx, cube->image, x, y);
        //     else if (cube->map[y][x] == 'W')
        //         mlx_image_to_window(cube->mlx, cube->image, x, y);
        //     x++;
        // }
        y++;
    }
    printf ("\n\n");
}

static void    hooks(t_cube *cube)
{
    if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(cube->mlx);
        exit(EXIT_SUCCESS);
    }
}

void	ft_render(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	hooks(cube);
    render_map(cube);
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
}
