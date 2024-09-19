/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:43:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/17 12:00:22 by hboudar          ###   ########.fr       */
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

static int	*get_rgb(t_cube *cube, char **tmp, int *rgb)
{
	int	f;
	int	j;
	int	i;

	if (!tmp)
		ft_eraser(cube, NULL, NULL, "Error : ft_split failed 1\n");
	(1) && (i = 0, f = 0, j = 0, rgb = malloc(sizeof(int) * 3));
	if (!rgb)
		ft_eraser(cube, tmp, NULL, "Error : malloc failed\n");
	while (tmp[1][i])
	{
		if (tmp[1][i] <= '9' && tmp[1][i] >= '0')
			rgb[j++] = costum_atoi(tmp[1] + i, &i);
		else if (tmp[1][i] == ',')
			(1) && (f++, i++);
		else
			ft_eraser(cube, tmp, rgb, "Error : Wrong RGB format\n");
	}
	if (f != 2 || rgb[0] == -1 || rgb[1] == -1 || rgb[2] == -1)
		ft_eraser(cube, tmp, rgb, "Error : Wrong RGB format\n");
	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	return (rgb);
}

void	get_element(t_cube *cube, char *element, char mode)
{
	int	start;

	(mode != 'F' && mode != 'C') && (start = skip_space(element + 3, 0));
	if (mode == 'N')
		cube->texture.no = ft_substr(element, start, ft_strlen(element) - 3);
	else if (mode == 'S')
		cube->texture.so = ft_substr(element, start, ft_strlen(element) - 3);
	else if (mode == 'W')
		cube->texture.we = ft_substr(element, start, ft_strlen(element) - 3);
	else if (mode == 'E')
		cube->texture.ea = ft_substr(element, start, ft_strlen(element) - 3);
	else if (mode == 'F')
		cube->texture.f = get_rgb(cube, ft_split(element, ' '), NULL);
	else if (mode == 'C')
		cube->texture.c = get_rgb(cube, ft_split(element, ' '), NULL);
	else
		ft_eraser(cube, NULL, NULL, "Error : Wrong format\n");
	cube->texture.flag++;
}

void	initialize_list(t_cube *cube, char *map)
{
	cube->fd = open(map, O_RDONLY);
	(cube->fd == -1) && (ft_error("Error : open failed\n"));
	cube->map_len = 0;
	cube->len_file = 0;
	cube->texture.flag = 0;
	cube->height = 0;
	cube->width = 0;
	cube->file = NULL;
	cube->map = NULL;
	cube->texture.no = NULL;
	cube->texture.so = NULL;
	cube->texture.we = NULL;
	cube->texture.ea = NULL;
	cube->texture.f = NULL;
	cube->texture.c = NULL;
	cube->player.x = 0;
	cube->player.y = 0;
	cube->player.radius = 3;
	cube->player.turn_direction = 0;
	cube->player.walk_direction = 0;
	cube->player.rotation_angle = M_PI / 2;
	cube->player.move_speed = 3.0;
	cube->player.rotation_speed = 3 * (M_PI / 180);
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
