/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:43:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/26 12:19:01 by hboudar          ###   ########.fr       */
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
	while (tmp[i])
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

	(mode != 'F' && mode != 'C') && (start = skip_space(elm + 3, 0));
	if (mode == 'N')
		cube->window.no = ft_substr(elm + 3, start, ft_strlen(elm) - 3);
	else if (mode == 'S')
		cube->window.so = ft_substr(elm + 3, start, ft_strlen(elm) - 3);
	else if (mode == 'W')
		cube->window.we = ft_substr(elm + 3, start, ft_strlen(elm) - 3);
	else if (mode == 'E')
		cube->window.ea = ft_substr(elm + 3, start, ft_strlen(elm) - 3);
	else if (mode == 'F' || mode == 'C')
	{
		tmp = ft_strtrim(elm, " ");
		(mode == 'F') && (cube->window.c = get_rgb(cube, tmp, NULL, 0));
		(mode == 'C') && (cube->window.f = get_rgb(cube, tmp, NULL, 0));
		free(tmp);
	}
	else
		ft_eraser(cube, NULL, NULL, "Error : Wrong format\n");
	cube->window.flag++;
}

void	initialize_list(t_cube *cube, char *map)
{
	cube->parsing.fd = open(map, O_RDONLY);
	if (cube->parsing.fd == -1)
		ft_error("Error : open failed\n");
	cube->parsing.map = NULL;
	cube->parsing.file = NULL;
	cube->parsing.map_len = 0;
	cube->parsing.len_file = 0;
	cube->window.flag = 0;
	cube->window.f = NULL;
	cube->window.c = NULL;
	cube->window.width = 0;
	cube->window.no = NULL;
	cube->window.so = NULL;
	cube->window.we = NULL;
	cube->window.ea = NULL;
	cube->window.height = 0;
	cube->player.x = 0;
	cube->player.y = 0;
	cube->player.radius = 3;
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
