/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/25 10:04:03 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "mlx.h"
#include <mlx.h>
#include <stdlib.h>

int    key_hook(int keycode, void *param)
{
    if (keycode == 53)
        exit(0);
    return (0);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    mlx_key_hook(mlx_win, key_hook, (void *)0);
	mlx_loop(mlx);
}