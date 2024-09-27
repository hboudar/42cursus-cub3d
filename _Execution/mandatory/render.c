/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:51 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/27 12:45:20 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_sky(t_cube *cube, t_exec *exec, t_player *player, t_win *win)
{
	exec->i = 0;
	while (exec->i < exec->walltop_pixel)
	{
		mlx_put_pixel(cube->image, exec->ray, exec->i,
			ft_pixel(win->c[0], win->c[1], win->c[2], 255));
		exec->i++;
	}
	(player->way == 'E') && (exec->texture_x
			= fmod(win->ray_intercept, TILE_SIZE) * win->t1->width / TILE_SIZE);
	(player->way == 'W') && (exec->texture_x
			= fmod(win->ray_intercept, TILE_SIZE) * win->t2->width / TILE_SIZE);
	(player->way == 'N') && (exec->texture_x
			= fmod(win->ray_intercept, TILE_SIZE) * win->t3->width / TILE_SIZE);
	(player->way == 'S') && (exec->texture_x
			= fmod(win->ray_intercept, TILE_SIZE) * win->t4->width / TILE_SIZE);
}

void	render_floor(t_cube *cube, t_exec *exec, t_win *win)
{
	exec->i = exec->wallbottom_pixel;
	while (exec->i < HEIGHT)
	{
		mlx_put_pixel(cube->image, exec->ray, exec->i,
			ft_pixel(win->f[0], win->f[1], win->f[2], 255));
		exec->i++;
	}
}

void	render_wall(t_cube *cube, t_exec *exec, t_player *ply, t_win *win)
{
	while (exec->i < exec->wallbottom_pixel)
	{
		(ply->way == 'E') && (exec->texture_y
				= (exec->i - exec->walltop_pixel)
				* win->t1->height / exec->wallstripheight);
		(ply->way == 'E') && (exec->color
				= get_pixel(win->t1, exec->texture_x, exec->texture_y));
		(ply->way == 'W') && (exec->texture_y
				= (exec->i - exec->walltop_pixel)
				* win->t2->height / exec->wallstripheight);
		(ply->way == 'W') && (exec->color
				= get_pixel(win->t2, exec->texture_x, exec->texture_y));
		(ply->way == 'N') && (exec->texture_y
				= (exec->i - exec->walltop_pixel)
				* win->t3->height / exec->wallstripheight);
		(ply->way == 'N') && (exec->color
				= get_pixel(win->t3, exec->texture_x, exec->texture_y));
		(ply->way == 'S') && (exec->texture_y
				= (exec->i - exec->walltop_pixel)
				* win->t4->height / exec->wallstripheight);
		(ply->way == 'S') && (exec->color
				= get_pixel(win->t4, exec->texture_x, exec->texture_y));
		mlx_put_pixel(cube->image, exec->ray, exec->i, exec->color);
		exec->i++;
	}
}

void	render_window(t_cube *cube, t_exec *exec, t_player *player, t_win *wind)
{
	exec->correct_distance = cube->player.true_distance
		* cos(cube->player.rotation_angle - exec->ray_angle);
	exec->distance_proj_plane = ((double)WIDTH / 2) / tan(FOV / 2);
	exec->wallstripheight = (TILE_SIZE / exec->correct_distance)
		* exec->distance_proj_plane;
	exec->walltop_pixel = ((double)HEIGHT / 2) - (exec->wallstripheight / 2);
	exec->wallbottom_pixel = ((double)HEIGHT / 2) + (exec->wallstripheight / 2);
	if (exec->wallbottom_pixel > HEIGHT)
		exec->wallbottom_pixel = HEIGHT;
	if (exec->walltop_pixel < 0)
		exec->walltop_pixel = 0;
	if (exec->wallstripheight >= HEIGHT)
		exec->walltop_pixel -= (exec->wallstripheight - HEIGHT) / 2;
	render_sky(cube, exec, player, wind);
	render_wall(cube, exec, player, wind);
	render_floor(cube, exec, wind);
}
