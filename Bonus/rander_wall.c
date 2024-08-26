/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:13:22 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/25 20:24:07 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdint.h>
#include <stdio.h>

int    get_pixel(mlx_texture_t *texture, int x, int y)
{
    int    index;

    index = (y * texture->width + x) * texture->bytes_per_pixel;
    // if (index < 0 || index >= (texture->width * texture->height * texture->bytes_per_pixel))
    //     return (0);
    return (ft_pixel(texture->pixels[index], texture->pixels[index + 1],
            texture->pixels[index + 2], texture->pixels[index + 3]));
}


void render_wall(t_cube *cube, mlx_image_t *image, double angle, double ray)
{
    uint32_t color = 0;
    uint32_t texture_x = 0;
     uint32_t texture_y = 0;
    double wallstripheight;
    double correct_distance = cube->true_distance * cos(cube->player_angle - angle);
    double distance_proj_plane = (WIDTH / 2) / tan(FOV / 2);
    wallstripheight = (TILE_SIZE / correct_distance) * distance_proj_plane;
    
    int walltop_pixel = (HEIGHT / 2) - (wallstripheight / 2);
    int wallbottom_pixel = (HEIGHT / 2) + (wallstripheight / 2);
    // wallbottom_pixel += cube->up;
    // walltop_pixel += cube->up;
    
    if (wallbottom_pixel > HEIGHT)
        wallbottom_pixel = HEIGHT;
        
    if (walltop_pixel < 0)
        walltop_pixel = 0;
    if (wallstripheight >= HEIGHT)
        walltop_pixel -= (wallstripheight - HEIGHT) / 2;

    int j = 0;
    while (j < walltop_pixel)
    {
        mlx_put_pixel(image, ray, j, ft_pixel(cube->textures.c[0], cube->textures.c[1], cube->textures.c[2], 0xFF)); // Sky blue
        j++;
    }
    // if (cube->ray_intercept < 0)
    //     cube->ray_intercept = 0;
    if (cube->direction == EAST)
        texture_x = fmod(cube->ray_intercept, TILE_SIZE) * cube->wall_1->width / TILE_SIZE;
    else if (cube->direction == WEST)
        texture_x = fmod(cube->ray_intercept, TILE_SIZE) * cube->wall_4->width / TILE_SIZE;
    else if (cube->direction == NORTH)
        texture_x = fmod(cube->ray_intercept, TILE_SIZE) * cube->wall_2->width / TILE_SIZE;
    else if (cube->direction == SOUTH)
        texture_x = fmod(cube->ray_intercept, TILE_SIZE) * cube->wall_3->width / TILE_SIZE;
    while (j < wallbottom_pixel)
    {
        if (cube->direction == EAST)
            texture_y = (j - walltop_pixel) * cube->wall_1->height / wallstripheight;
        else if (cube->direction == WEST)
            texture_y = (j - walltop_pixel) * cube->wall_4->height / wallstripheight;
        else if (cube->direction == NORTH)
            texture_y = (j - walltop_pixel) * cube->wall_2->height / wallstripheight;
        else if (cube->direction == SOUTH)
            texture_y = (j - walltop_pixel) * cube->wall_3->height / wallstripheight;
        if (cube->direction == EAST)
            color = get_pixel(cube->wall_1, texture_x, texture_y);
        else if (cube->direction == WEST)
            color = get_pixel(cube->wall_4, texture_x, texture_y);
        else if (cube->direction == NORTH)
            color = get_pixel(cube->wall_2, texture_x, texture_y);
        else if (cube->direction == SOUTH)
            color = get_pixel(cube->wall_3, texture_x, texture_y);
        mlx_put_pixel(image, ray, j, color);
        j++;
    }
    j = wallbottom_pixel;
    while (j < HEIGHT)
    {
        mlx_put_pixel(image, ray, j, ft_pixel(cube->textures.f[0], cube->textures.f[1], cube->textures.f[2], 0xFF)); // Floor white
        j++;
    }
}
