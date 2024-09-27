/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:51 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/27 13:17:01 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_line(t_cube *cube, int length, int curr_x, int curr_y)
{
	int			x_end;
	int			y_end;
	int			sx;
	int			sy;
	int			err;
	int			dx;
	int			dy;
	x_end = curr_x + cos(cube->player.rotation_angle) * length;
	y_end = curr_y + sin(cube->player.rotation_angle) * length;
	dx = abs(x_end - curr_x);
	dy = abs(y_end - curr_y);
	(1) && (sx = -1, sy = -1, err = dx - dy);
	(curr_x < x_end) && (sx = 1);
	(curr_y < y_end) && (sy = 1);
	while (curr_x != x_end || curr_y != y_end)
	{
		mlx_put_pixel(cube->image, curr_x, curr_y,
			ft_pixel(rand() % 255, rand() % 255, rand() % 255, 255));
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; curr_x += sx; }
		if (e2 < dx) { err += dx; curr_y += sy; }
	}
}

static void	draw_circle(mlx_image_t *image, t_player *player)
{
	int			x;
	int			y;
	y = -player->radius;
	while (y <= player->radius)
	{
		x = -player->radius;
		while (x <= player->radius)
		{
			if ((x * x) + (y * y) <= (player->radius * player->radius))
				mlx_put_pixel(image, player->x + x, player->y + y,
				ft_pixel(rand() % 255, rand() % 255, rand() % 255, 255));
			x++;
		}
		y++;
	}
}

void	render_map(t_cube *cube, t_player *player, char **map)
{
	uint32_t	color;
	int			x;
	int			y;

	y = 0;
	player->radius = 3;
    while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			(map[y][x] != '1') && (color = ft_pixel(0, 0, 0, 255));
			(map[y][x] == '1') && (color = ft_pixel(255, 255, 255, 255));
			if (map[y][x] != ' ')
				ft_pixel_to_image(cube->image,
					x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	draw_circle(cube->image, player);
    draw_line(cube, 8, player->x, player->y);
}

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
