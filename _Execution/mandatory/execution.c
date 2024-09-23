/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:37:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/23 16:34:23 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


void	draw_utils(t_cube *cube, mlx_image_t *image, double angle)
{
	int	j;
	int	x;
	int	y;

	j = 0;
	while (j < cube->true_distance)
	{
		x = cube->player.x + j * cos(angle);
		y = cube->player.y + j * sin(angle);
		if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
			break ;
		// mlx_put_pixel(image, x, y, ft_pixel(0x80, 0x00, 0x00, 0xFF));
		mlx_put_pixel(image, x, y, ft_pixel(rand() % 255, rand() % 255, rand() % 255, 255));
		j++;
	}
}

//color : ra

int check_wall(double x, double y, t_cube *cube)
{

    int map_x = floor(x / TILE_SIZE);
    int map_y = floor(y / TILE_SIZE);
    if (map_x < 0 || map_x >= cube->width || map_y < 0 || map_y >= cube->height)
        return (1);
    if ((int)ft_strlen(cube->map[map_y]) <= map_x)
        return (1);
    if (cube->map[map_y][map_x] == '1')
        return (1);
    return (0);
}


void get_oriz(t_cube *cube, double angle)
{
    double y_intercept = floor(cube->player.y / TILE_SIZE) * TILE_SIZE;
    if (cube->facing_down)
        y_intercept += TILE_SIZE;
    double x_intercept = cube->player.x + (y_intercept - cube->player.y) / tan(angle);
    double y_step = TILE_SIZE;
    double x_step = TILE_SIZE / tan(angle);
    if (cube->facing_up)
        y_step *= -1;
    if (cube->facing_right && x_step < 0)
        x_step *= -1;
    if (cube->facing_left && x_step > 0)
        x_step *= -1;

    if (cube->facing_up)
        y_intercept -= 0.0001;
    while (1)
    {
        if (check_wall(x_intercept, y_intercept, cube))
        {
            cube->orizontal_position_x = x_intercept;
            cube->orizontal_position_y = y_intercept;
            break;
        }
        else
        {
            x_intercept += x_step;
            y_intercept += y_step;
        }
    }
}    

void get_vert(t_cube *cube, double angle)
{
    double x_intercept = floor(cube->player.x / TILE_SIZE) * TILE_SIZE;
    if (cube->facing_right)
        x_intercept += TILE_SIZE;
    double y_intercept = cube->player.y+ (x_intercept - cube->player.x) * tan(angle);

    double x_step = TILE_SIZE;
    double y_step = TILE_SIZE * tan(angle);
    if (cube->facing_left)
        x_step *= -1;
    
    if (cube->facing_down && y_step < 0)
        y_step *= -1;
    if (cube->facing_up && y_step > 0)
        y_step *= -1;

    if (cube->facing_left)
        x_intercept -= 0.0001; 
    while (1)
    {
        if (check_wall(x_intercept, y_intercept, cube))
        {
            cube->vertical_position_x = x_intercept;
            cube->vertical_position_y = y_intercept;
            break;
        }
        else
        {
            x_intercept += x_step;
            y_intercept += y_step;
        }
    }
}

double smallest_distance(t_cube *cube, double angle)
{
    (void)angle;
    double distance_oriz = sqrt(pow(cube->player.x - cube->orizontal_position_x, 2) + pow(cube->player.y - cube->orizontal_position_y, 2));
    double distance_vert = sqrt(pow(cube->player.x - cube->vertical_position_x, 2) + pow(cube->player.y - cube->vertical_position_y, 2));
    if (distance_oriz < distance_vert)
        return (distance_oriz);
    return (distance_vert);
}

void cast_ray(t_cube *cube, double angle)
{
    // angle = normalize_angle(angle);
    cube->facing_down = (angle > 0 && angle < M_PI) * 1;
    cube->facing_up = !cube->facing_down;
    cube->facing_right = (angle < (0.5 * M_PI) || angle > (1.5 * M_PI));
    cube->facing_left = !cube->facing_right;
    get_oriz(cube, angle);
    get_vert(cube, angle);
    cube->true_distance = smallest_distance(cube, angle);
}

void ray_casting(t_cube *cube)
{
    double angle = normalize_angle(cube->player.rotation_angle) - (FOV / 2);
    int rays = -1;
    while (++rays < WIDTH)
    {
        cast_ray(cube, angle);
		draw_utils(cube, cube->image, angle);
        // render_wall(cube, image, angle, rays);
        angle += FOV / WIDTH;
        angle = normalize_angle(angle);
    }
}

void	rotations(void *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->rotation_angle += ROTATION_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->rotation_angle -= ROTATION_SPEED;
	player->rotation_angle = remainder(player->rotation_angle, 2 * M_PI);
	if (player->rotation_angle < 0)
		player->rotation_angle = (2 * M_PI) + player->rotation_angle;
}

void	hooks(t_cube *cube, t_player *player, double move_x, double move_y)
{
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
	{
		move_x = cos(player->rotation_angle) * MOVE_SPEED;
		move_y = sin(player->rotation_angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
	{
		move_x = cos(player->rotation_angle) * -MOVE_SPEED;
		move_y = sin(player->rotation_angle) * -MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
	{
		move_x = -sin(player->rotation_angle) * MOVE_SPEED;
		move_y = cos(player->rotation_angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
	{
		move_x = sin(player->rotation_angle) * MOVE_SPEED;
		move_y = -cos(player->rotation_angle) * MOVE_SPEED;
	}
	check_move(cube, move_x, move_y);
}

void	execution(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	hooks(cube, &cube->player, 0.0, 0.0);
	rotations(cube->mlx, &cube->player);
	render_map(cube, &cube->player, cube->map);
	ray_casting(cube);
	draw_line(cube, 50, cube->player.x, cube->player.y);
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
		ft_error("Error : Image not found\n");
}
