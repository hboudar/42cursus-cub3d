/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:01:36 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/08 15:50:52 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_map(t_cube *cube, char *tmp1, char **tmp2, int i)
{
	int	j;

	(1) && (j = 0, tmp1 = ft_strtrim(cube->file[i], "1 "));
	if (!ft_strchr(cube->file[i], '1') || (tmp1 && tmp1[0] != '\0'))
		ft_eraser(cube, NULL, (void *)tmp1, "Error : invalid map\n");
	(tmp1) && (free (tmp1), tmp1 = NULL);
	cube->map = (char **)malloc(sizeof(char *) * (cube->len_file - i + 1));
	if (!cube->map)
		ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
	take_map(cube, 0, 0, 0);
	i = 0;
	while (ft_strlen(cube->map[i]) == 0 || skip_space(cube->map[i]))
		i++;
	tmp2 = (char **)malloc(sizeof(char *) * ((cube->len_file - 6 - i) + 1));
	if (!tmp2)
		ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
	while (cube->map[i])
	{
		tmp2[j] = ft_strdup(cube->map[i]);
		i++;
		j++;
	}
	tmp2[j] = NULL;
	free(cube->map);
	cube->map = tmp2;
}

void	parse_textures(t_cube *cube, int i)
{
	if (!cube->file)
		ft_error("Error : ft_split failed\n");
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
	if (parse_mape2(cube))
		ft_error("Error : Map is invalid 2\n");
}
