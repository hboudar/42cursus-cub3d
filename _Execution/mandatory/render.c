/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:51 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/26 11:56:32 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		mlx_put_pixel(cube->image, curr_x + 160, curr_y + 160,
			ft_pixel(rand() % 255, rand() % 255, rand() % 255, 255));
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; curr_x += sx; }
		if (e2 < dx) { err += dx; curr_y += sy; }
	}
}

void	draw_rays(t_cube *cube, mlx_image_t *image, double angle)
{
	int	j;
	int	x;
	int	y;

	j = 0;
	while (j < cube->player.true_distance)
	{
		x = cube->player.x + j * cos(angle);
		y = cube->player.y + j * sin(angle);
		if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
			break ;
		mlx_put_pixel(image, x + 160, y + 160, ft_pixel(0, 0, 100, 255));
		j++;
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
				mlx_put_pixel(image, player->x + x + 160, player->y + y + 160,
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
}
//render wall :
// int    get_pixel(mlx_texture_t *texture, int x, int y)
// {
//     int    index;

//     index = (y * texture->width + x) * texture->bytes_per_pixel;
//     return (ft_pixel(texture->pixels[index], texture->pixels[index + 1],
//             texture->pixels[index + 2], texture->pixels[index + 3]));
// }

// void render_wall(t_cube *cube, mlx_image_t *image, double angle, double ray)
// {
//     uint32_t color = 0;
//     uint32_t texture_x = 0;
//      uint32_t texture_y = 0;
//     double wallstripheight;
//     double correct_distance = cube->player.true_distance * cos(cube->player.rotation_angle - angle);
//     double distance_proj_plane = (WIDTH / 2) / tan(FOV / 2);
//     wallstripheight = (TILE_SIZE / correct_distance) * distance_proj_plane;
    
//     int walltop_pixel = (HEIGHT / 2) - (wallstripheight / 2);
//     int wallbottom_pixel = (HEIGHT / 2) + (wallstripheight / 2);
//     if (wallbottom_pixel > HEIGHT)
//         wallbottom_pixel = HEIGHT;
//     if (walltop_pixel < 0)
//         walltop_pixel = 0;
//     if (wallstripheight >= HEIGHT)
//         walltop_pixel -= (wallstripheight - HEIGHT) / 2;
//     int j = 0;
//     while (j < walltop_pixel)
//     {
//         mlx_put_pixel(image, ray, j, ft_pixel(cube->window.c[0], cube->window.c[1], cube->window.c[2], 0xFF)); // Sky blue
//         j++;
//     }
//     (cube->player.direction == 'E') && (texture_x = fmod(cube->ray_intercept, TILE_SIZE) * cube->wall_1->width / TILE_SIZE);
//     (cube->player.direction == 'W') && (texture_x = fmod(cube->ray_intercept, TILE_SIZE) * cube->wall_2->width / TILE_SIZE);
//     (cube->player.direction == 'N') && (texture_x = fmod(cube->ray_intercept, TILE_SIZE) * cube->wall_3->width / TILE_SIZE);
//     (cube->player.direction == 'S') && (texture_x = fmod(cube->ray_intercept, TILE_SIZE) * cube->wall_4->width / TILE_SIZE);
//     while (j < wallbottom_pixel)
//     {        (cube->player.direction == 'E') && (texture_y = (j - walltop_pixel) * cube->wall_1->height / wallstripheight);
//         (cube->player.direction == 'W') && (texture_y = (j - walltop_pixel) * cube->wall_2->height / wallstripheight);
//         (cube->player.direction == 'N') && (texture_y = (j - walltop_pixel) * cube->wall_3->height / wallstripheight);
//         (cube->player.direction == 'S') && (texture_y = (j - walltop_pixel) * cube->wall_4->height / wallstripheight);
//         (cube->player.direction == 'E') && (color = get_pixel(cube->wall_1, texture_x, texture_y));
//         (cube->player.direction == 'W') && (color = get_pixel(cube->wall_2, texture_x, texture_y));
//         (cube->player.direction == 'N') && (color = get_pixel(cube->wall_3, texture_x, texture_y));
//         (cube->player.direction == 'S') && (color = get_pixel(cube->wall_4, texture_x, texture_y));
//         mlx_put_pixel(image, ray, j, color);
//         j++;
//     }
//     j = wallbottom_pixel;
//     while (j < HEIGHT)
//     {
//         mlx_put_pixel(image, ray, j, ft_pixel(cube->window.f[0], cube->window.f[1], cube->window.f[2], 0xFF)); // Floor white
//         j++;
//     }
// }