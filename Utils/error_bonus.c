/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:56:35 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/20 10:38:19 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	ft_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	ft_eraser(t_cube *cube, void *tmp, int *rgb, char *msg)
{
	int		i;
	t_win	*win;

	i = -1;
	win = &cube->win;
	(win->no) && (free(win->no), win->no = NULL);
	(win->so) && (free(win->so), win->so = NULL);
	(win->we) && (free(win->we), win->we = NULL);
	(win->ea) && (free(win->ea), win->ea = NULL);
	(win->f) && (free(win->f), win->f = NULL);
	(win->c) && (free(win->c), win->c = NULL);
	(tmp) && (free(tmp), tmp = NULL);
	(rgb) && (free(rgb), rgb = NULL);
	(cube->pars.fd) && (close(cube->pars.fd), cube->pars.fd = 0);
	ft_error(msg);
}
