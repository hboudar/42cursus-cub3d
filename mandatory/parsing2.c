/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:01:28 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/10 14:56:16 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int	skip_line(t_cube *cube, int i, int mode)
{
	if (mode)
	{
		mode = 0;
		while (cube->fd_file[i] && cube->fd_file[i] != '\n')
			(1) && (i++, mode++);
		if (cube->fd_file[i] == '\n')
			(1) && (i++, mode++);
	}
	else
	{
		while (cube->fd_file[i] && cube->fd_file[i] != '\n')
		{
			i++;
			mode++;
		}
	}
	return (mode);
}

static int	next_check(char **map, int x, int y)
{
	if (map[x + 1][y] != '0' && map[x + 1][y] != '1' &&
			map[x + 1][y] != 'N' && map[x + 1][y] != 'S' &&
			map[x + 1][y] != 'W' && map[x + 1][y] != 'E')
		return (0);
	if (map[x - 1][y] != '0' && map[x - 1][y] != '1' &&
			map[x - 1][y] != 'N' && map[x - 1][y] != 'S' &&
			map[x - 1][y] != 'W' && map[x - 1][y] != 'E')
		return (0);
	if (map[x][y + 1] != '0' && map[x][y + 1] != '1' &&
			map[x][y + 1] != 'N' && map[x][y + 1] != 'S' &&
			map[x][y + 1] != 'W' && map[x][y + 1] != 'E')
		return (0);
	if (map[x][y - 1] != '0' && map[x][y - 1] != '1' &&
			map[x][y - 1] != 'N' && map[x][y - 1] != 'S' &&
			map[x][y - 1] != 'W' && map[x][y - 1] != 'E')
		return (0);
	return (1);
}

int	check_map(char **map, int x, int y)
{
	while (map[x + 1] != NULL)
	{
		y = 0;
		if (ft_strlen(map[x]) == 0 || skip_space(map[x]))
			return (0);
		while (map[x][y])
		{
			if ((map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S' ||
						map[x][y] == 'W' || map[x][y] == 'E')
					&& (map[x + 1][y] && map[x - 1][y] &&
						map[x][y + 1] && map[x][y - 1]))
			{
				if (!next_check(map, x, y))
					return (0);
			}
			else if (map[x][y] == '0' || map[x][y] == 'N' ||
					map[x][y] == 'S' || map[x][y] == 'W' ||
					map[x][y] == 'E')
				return (0);
			y++;
		}
		x++;
	}
	return (x);
}

int	check_elem(char **map, t_cube *cube)
{
	int	count;
	int	x;
	int	y;

	(1) && (count = 0, x = 0);
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] != '0' && map[x][y] != '1' && map[x][y] != 'N'
					&& map[x][y] != 'S' && map[x][y] != 'W' && map[x][y] != 'E'
					&& map[x][y] != ' ')
				return (0);
			else if (map[x][y] == 'N' || map[x][y] == 'S'
					|| map[x][y] == 'W' || map[x][y] == 'E')
				count++;
			y++;
		}
		(y > cube->width) && (cube->width = y);
		x++;
	}
	cube->height = x;
	return (count);
}
