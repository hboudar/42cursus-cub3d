/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:36:47 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/10 14:55:13 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg)
{
	int	i;

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