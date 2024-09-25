/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:01:36 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/16 17:49:40 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	take_map(t_cube *cube, int i, int j, int k)
{
	while (cube->fd_file[i])
	{
		if (cube->fd_file[i] == 'N' || cube->fd_file[i] == 'S' || \
			cube->fd_file[i] == 'W' || cube->fd_file[i] == 'E' || \
			cube->fd_file[i] == 'F' || cube->fd_file[i] == 'C')
			i += skip_line(cube, i, 1);
		else
		{
			k = 0;
			cube->map[j] = malloc(sizeof(char) * (skip_line(cube, i, 0) + 1));
			while (cube->fd_file[i] && cube->fd_file[i] != '\n')
				(1) && (cube->map[j][k] = cube->fd_file[i], (i++, k++));
			if (cube->fd_file[i] == '\n')
				i++;
			cube->map[j][k] = '\0';
			j++;
		}
	}
	cube->map[j] = NULL;
}

static int	parse_mape2(t_cube *cube)
{
	char	*tmp;
	int		r;

	r = check_elem(cube->map, cube);
	if (!r || r != 1)
		return (1);
	r = check_map(cube->map, 1, 0);
	if (r)
	{
		tmp = ft_strtrim(cube->map[r], "1 ");
		if ((tmp && tmp[0] != '\0') || !ft_strlen(cube->map[r]))
			ft_eraser(cube, NULL, (void *)tmp, "Error : invalid map\n");
		(tmp) && (free (tmp), tmp = NULL);
	}
	else
		return (1);
	return (0);
}

static void	parse_map(t_cube *cube, char *tmp1, char **tmp2, int i)
{
	int	j;

	j = 0;
	tmp1 = ft_strtrim(cube->file[i], "1 ");
	if (!ft_strchr(cube->file[i], '1') || (tmp1 && tmp1[0] != '\0'))
		ft_eraser(cube, NULL, (void *)tmp1, "Error : invalid map\n");
	(tmp1) && (free (tmp1), tmp1 = NULL);
	cube->map = (char **)malloc(sizeof(char *) * (cube->len_file - i + 1));
	if (!cube->map)
		ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
	take_map(cube, 0, 0, 0);
	i = 0;
	while (ft_strlen(cube->map[i]) == 0 || skip_space(cube->map[i], 1))
		i++;
	tmp2 = (char **)malloc(sizeof(char *) * ((cube->len_file - 6 - i) + 1));
	if (!tmp2)
		ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
	while (cube->map[i])
		(1) && (tmp2[j] = ft_strdup(cube->map[i]), i++, j++);
	tmp2[j] = NULL;
	free(cube->map);
	cube->map = tmp2;
}

static void	parse_textures(t_cube *cube, int i)
{
	(!cube->file) && (ft_error("Error : ft_split failed\n"));
	while (cube->file[i] && i < 7)
	{
		if (!ft_strncmp(cube->file[i], "NO ", 3))
			get_element(cube, cube->file[i], 'N');
		else if (!ft_strncmp(cube->file[i], "SO ", 3))
			get_element(cube, cube->file[i], 'S');
		else if (!ft_strncmp(cube->file[i], "WE ", 3))
			get_element(cube, cube->file[i], 'W');
		else if (!ft_strncmp(cube->file[i], "EA ", 3))
			get_element(cube, cube->file[i], 'E');
		else if (!ft_strncmp(cube->file[i], "F ", 2))
			get_element(cube, cube->file[i], 'F');
		else if (!ft_strncmp(cube->file[i], "C ", 2))
			get_element(cube, cube->file[i], 'C');
		i++;
	}
	if (cube->texture.flag != 6)
		ft_error("Error : elements are not valid\n");
	else if (!cube->texture.no || !cube->texture.so || !cube->texture.we
		|| !cube->texture.ea || !cube->texture.f || !cube->texture.c)
		ft_error("Error : an element is missing\n");
}

void	is_map_valid(int argc, char *argv[], t_cube *cube)
{
	char	*line;
	char	*tmp;

	check_map_name(argc, argv[1], 0);
	initialize_list(cube, argv[1]);
	tmp = ft_strdup("");
	line = get_next_line(cube->fd);
	while (line)
	{
		tmp = ft_strjoin(tmp, line);
		line = get_next_line(cube->fd);
		cube->len_file++;
	}
	cube->fd_file = tmp;
	cube->file = ft_split(tmp, '\n');
	if (!cube->file)
		ft_eraser(cube, NULL,
			(void *)tmp, "Error : ft_split failed\n");
	parse_textures(cube, 0);
	parse_map(cube, NULL, NULL, 6);
	(parse_mape2(cube)) && (ft_error("Error : Map is invalid 2\n"));
}
