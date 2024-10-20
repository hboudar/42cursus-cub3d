/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:17:03 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/20 11:06:27 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	costum_atoi(char *str, int *index)
{
	int	res;
	int	i;

	(1) && (i = 0, res = 0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
		if (res > 255 || res < 0)
		{
			*index += i;
			return (-1);
		}
	}
	*index += i;
	return (res);
}

static int	*get_rgb(t_cube *cube, char *tmp, int *rgb, int f)
{
	int	j;
	int	i;

	if (!tmp)
		ft_eraser(cube, NULL, NULL, "Error : ft_split failed\n");
	(1) && (i = 1, f = 0, j = 0, rgb = malloc(sizeof(int) * 3));
	if (!rgb)
		ft_eraser(cube, tmp, NULL, "Error : malloc failed\n");
	while (tmp[i] && j < 3)
	{
		if (tmp[i] == ' ')
			i++;
		else if (tmp[i] <= '9' && tmp[i] >= '0')
			rgb[j++] = costum_atoi(tmp + i, &i);
		else if (tmp[i] == ',')
			(1) && (f++, i++);
		else
			ft_eraser(cube, tmp, rgb, "Error : Wrong RGB format\n");
	}
	while (tmp[i] && tmp[i] == ' ')
		i++;
	if (tmp[i] || j != 3 || f != 2
		|| rgb[0] == -1 || rgb[1] == -1 || rgb[2] == -1)
		ft_eraser(cube, tmp, rgb, "Error : Wrong RGB format\n");
	return (rgb);
}

void	get_element(t_cube *cube, char *elm, char mode)
{
	char	*tmp;
	int		start;

	if (mode != 'F' && mode != 'C')
		start = skip_space(elm + 3, 0);
	if (mode == 'N' && !cube->win.no)
		cube->win.no = ft_substr(elm + 3, start, ft_strlen(elm) - 3);
	else if (mode == 'S' && !cube->win.so)
		cube->win.so = ft_substr(elm + 3, start, ft_strlen(elm) - 3);
	else if (mode == 'W' && !cube->win.we)
		cube->win.we = ft_substr(elm + 3, start, ft_strlen(elm) - 3);
	else if (mode == 'E' && !cube->win.ea)
		cube->win.ea = ft_substr(elm + 3, start, ft_strlen(elm) - 3);
	else if ((mode == 'F' && !cube->win.f) || (mode == 'C' && !cube->win.c))
	{
		tmp = ft_strtrim(elm, " ");
		(mode == 'F') && (cube->win.f = get_rgb(cube, tmp, NULL, 0));
		(mode == 'C') && (cube->win.c = get_rgb(cube, tmp, NULL, 0));
		free(tmp);
	}
	else
		ft_eraser(cube, NULL, NULL, "Error : invalid element(s)\n");
	cube->win.flag++;
}

void	initialize_list(t_cube *cube, char *map)
{
	cube->pars.fd = open(map, O_RDONLY);
	if (cube->pars.fd == -1)
		ft_error("Error : open failed\n");
	(1) && (cube->pars.map = NULL, cube->pars.file = NULL);
	(1) && (cube->win.f = NULL, cube->win.c = NULL);
	(1) && (cube->win.no = NULL, cube->win.so = NULL);
	(1) && (cube->win.ea = NULL, cube->win.we = NULL);
	(1) && (cube->win.width = 0, cube->win.height = 0);
	(1) && (cube->player.x = 0, cube->player.y = 0);
	cube->pars.map_len = 0;
	cube->pars.len_file = 0;
	cube->win.flag = 0;
	cube->player.rotation_angle = M_PI / 2;
}

void	check_map_name(int argc, char *name, int i)
{
	if (name == NULL)
		ft_error("Error : No file\n");
	else if (argc > 2)
		ft_error("Error : Too many arguments\n");
	while (name[i])
		i++;
	if (i < 4 || name[i - 1] != 'b' || name[i - 2] != 'u' \
			|| name[i - 3] != 'c' || name[i - 4] != '.')
		ft_error("Error : Wrong file extension\n");
	else if (access(name, F_OK) == -1)
		ft_error("Error : File doesn't exist\n");
	else if (access(name, R_OK) == -1)
		ft_error("Error : File is not readable\n");
}
