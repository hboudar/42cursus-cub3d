/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:51 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/16 09:27:41 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void render_map(t_cube *cube)
{
    int x;
    int y;

    y = 0;
    while (y < 10)
    {
        x = 0;
        while (x < 10)
        {
            mlx_put_pixel(cube->image, x * 100, y * 10, 0x00FF0000);
            x++;
        }
        y++;
    }
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
}
