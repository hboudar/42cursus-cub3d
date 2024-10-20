/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:21:19 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/20 10:31:34 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	add_spaces(t_cube *cube, char *tmp, int x, int y)
{
	int		found;

	y = -1;
	while (++y < cube->win.height)
	{
		if (y == cube->win.height - 1 && !ft_strlen(cube->pars.map[y]))
			break ;
		tmp = malloc(sizeof(char) * (cube->win.width + 1));
		if (!tmp)
			ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
		(1) && (found = 0, x = -1);
		while (++x < cube->win.width)
		{
			if (found || cube->pars.map[y][x] == '\0')
			{
				tmp[x] = ' ';
				found = 1;
			}
			else
				tmp[x] = cube->pars.map[y][x];
		}
		tmp[x] = '\0';
		free(cube->pars.map[y]);
		cube->pars.map[y] = tmp;
	}
}
