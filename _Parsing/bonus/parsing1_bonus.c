/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:01:36 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/27 12:51:39 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	take_map(t_pars *parsing, int i, int j, int k)
{
	while (parsing->fd_file[i])
	{
		if (parsing->fd_file[i] == 'N' || parsing->fd_file[i] == 'S' || \
			parsing->fd_file[i] == 'W' || parsing->fd_file[i] == 'E' || \
			parsing->fd_file[i] == 'F' || parsing->fd_file[i] == 'C')
			i += skip_line(parsing, i, 1);
		else
		{
			k = 0;
			parsing->map[j] = malloc(sizeof(char)
					* (skip_line(parsing, i, 0) + 1));
			while (parsing->fd_file[i] && parsing->fd_file[i] != '\n')
				(1) && (parsing->map[j][k] = parsing->fd_file[i], (i++, k++));
			if (parsing->fd_file[i] == '\n')
				i++;
			parsing->map[j][k] = '\0';
			j++;
		}
	}
	parsing->map[j] = NULL;
}

static int	parse_mape2(t_cube *cube, t_pars *parsing)
{
	char	*tmp;
	int		r;

	r = check_elem(parsing->map, cube);
	if (!r || r != 1)
		return (1);
	r = check_map(parsing->map, 1, 0);
	if (r)
	{
		tmp = ft_strtrim(parsing->map[r], "1 ");
		if ((tmp && tmp[0] != '\0') || !ft_strlen(parsing->map[r]))
			ft_eraser(cube, NULL, (void *)tmp, "Error : invalid map\n");
		(tmp) && (free (tmp), tmp = NULL);
	}
	else
		return (1);
	return (0);
}

static void	parse_map(t_cube *cube, t_pars *parsing, char *tmp1, char **tmp2)
{
	int	i;
	int	j;

	(1) && (j = 0, i = 6);
	tmp1 = ft_strtrim(parsing->file[i], "1 ");
	if (!ft_strchr(parsing->file[i], '1') || (tmp1 && tmp1[0] != '\0'))
		ft_eraser(cube, NULL, (void *)tmp1, "Error : invalid map\n");
	(tmp1) && (free (tmp1), tmp1 = NULL);
	parsing->map = (char **)malloc(sizeof(char *)
			* (parsing->len_file - i + 1));
	if (!parsing->map)
		ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
	take_map(parsing, 0, 0, 0);
	i = 0;
	while (ft_strlen(parsing->map[i]) == 0 || skip_space(parsing->map[i], 1))
		i++;
	tmp2 = (char **)malloc(sizeof(char *) * ((parsing->len_file - 6 - i) + 1));
	if (!tmp2)
		ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
	while (parsing->map[i])
		(1) && (tmp2[j] = ft_strdup(parsing->map[i]), i++, j++);
	tmp2[j] = NULL;
	free(parsing->map);
	parsing->map = tmp2;
}

void	parse_textures(t_cube *cube, t_pars *parsing, t_win *window)
{
	int	i;

	i = 0;
	(!parsing->file) && (ft_error("Error : ft_split failed\n"));
	while (parsing->file[i] && i < 7)
	{
		if (!ft_strncmp(parsing->file[i], "NO ", 3))
			get_element(cube, parsing->file[i], 'N');
		else if (!ft_strncmp(parsing->file[i], "SO ", 3))
			get_element(cube, parsing->file[i], 'S');
		else if (!ft_strncmp(parsing->file[i], "WE ", 3))
			get_element(cube, parsing->file[i], 'W');
		else if (!ft_strncmp(parsing->file[i], "EA ", 3))
			get_element(cube, parsing->file[i], 'E');
		else if (!ft_strncmp(parsing->file[i], "F ", 2))
			get_element(cube, parsing->file[i], 'F');
		else if (!ft_strncmp(parsing->file[i], "C ", 2))
			get_element(cube, parsing->file[i], 'C');
		i++;
	}
	if (window->flag != 6)
		ft_error("Error : elements are not valid\n");
	else if (!window->no || !window->so || !window->we || !window->ea
		|| !window->f || !window->c)
		ft_error("Error : an element is missing\n");
}

void	is_map_valid(int argc, char *argv[], t_cube *cube)
{
	char	*line;
	char	*tmp;

	check_map_name(argc, argv[1], 0);
	initialize_list(cube, argv[1]);
	tmp = ft_strdup("");
	line = get_next_line(cube->parsing.fd);
	while (line)
	{
		tmp = ft_strjoin(tmp, line);
		line = get_next_line(cube->parsing.fd);
		cube->parsing.len_file++;
	}
	cube->parsing.fd_file = tmp;
	cube->parsing.file = ft_split(tmp, '\n');
	if (!cube->parsing.file)
		ft_eraser(cube, NULL,
			(void *)tmp, "Error : ft_split failed\n");
	parse_textures(cube, &cube->parsing, &cube->window);
	parse_map(cube, &cube->parsing, NULL, NULL);
	if (parse_mape2(cube, &cube->parsing))
		ft_error("Error : Map is invalid 2\n");
}
