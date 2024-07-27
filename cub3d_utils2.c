/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:26:27 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/27 16:47:45 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_error(char *msg)
{
    ft_putstr_fd(msg, 2);
    exit (EXIT_FAILURE);
}

void    ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg)
{
    int i;
    
    i = -1;
    (cube->texture.no) && (free(cube->texture.no), cube->texture.no = NULL);
    (cube->texture.so) && (free(cube->texture.so), cube->texture.so = NULL);
    (cube->texture.we) && (free(cube->texture.we), cube->texture.we = NULL);
    (cube->texture.ea) && (free(cube->texture.ea), cube->texture.ea = NULL);
    (cube->texture.f) && (free(cube->texture.f), cube->texture.f = NULL);
    (cube->texture.c) && (free(cube->texture.c), cube->texture.c = NULL);
    while (tmp && tmp[++i])
        free(tmp[i]);
    (tmp) && (free(tmp), tmp = NULL);
    (rgb) && (free(rgb), rgb = NULL);
    ft_error(msg);
}

void    ft_init_texture(t_cube *cube)
{
    cube->map_len = 0;
    cube->file_len = 0;
    cube->texture.flag = 0;
    cube->file = NULL;
    cube->map = NULL;
    cube->texture.no = NULL;
    cube->texture.so = NULL;
    cube->texture.we = NULL;
    cube->texture.ea = NULL;
    cube->texture.f = NULL;
    cube->texture.c = NULL;
}
