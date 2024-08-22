/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:13:22 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/22 17:37:57 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void render_wall(t_cube *cube, mlx_image_t *image, double angle, int ray)
{
        double wallstripheight;
        int32_t wall_color =  ft_pixel(0x80, 0x80, 0x80, 0xFF); // Gray
        int32_t wall_top_color = ft_pixel(0x00, 0xFF, 0xFF, 0x0F);
        int32_t wall_bottom_color = ft_pixel(0x00, 0x00, 0x00, 0xFF); // Black
        
        double correct_distance = cube->true_distance * cos(cube->player_angle - angle);
        double distance_proj_plane = (WIDTH / 2) / tan(FOV / 2);
        wallstripheight = (TILE_SIZE / correct_distance) * distance_proj_plane;
        int walltop_pixel = (HEIGHT / 2) - (wallstripheight / 2);
        if (walltop_pixel < 0)
            walltop_pixel = 0;
        int wallbottom_pixel = (HEIGHT / 2) + (wallstripheight / 2);
        if (wallbottom_pixel > HEIGHT)
            wallbottom_pixel = HEIGHT;
        int j = 0;
        while (j < walltop_pixel)
        {
            mlx_put_pixel(image, ray, j, wall_top_color);
            j++;
        }
        while (j < wallbottom_pixel)
        {
            
            mlx_put_pixel(image, ray, j, wall_color);
            j++;
        }

        while (j < HEIGHT)
        {
            mlx_put_pixel(image, ray, j, wall_bottom_color);
            j++;
        }
}