/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:01:36 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/27 17:18:53 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    parse_mape(t_cube *cube)
{
    char    **tmp;
    int     i;

    i = 6;
    if (!cube->file[i] || !ft_strchr(cube->file[6], '1'))
        ft_eraser(cube, NULL, NULL, "Error : invalid map\n");
    cube->map = (char **)malloc(sizeof(char *) * (cube->file_len + 1));
    if (!cube->map)
        ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
    take_map(cube, 0, 0, 0);
    i = 0;
    while (ft_strlen(cube->map[i]) == 0)
        i++;
    tmp = (char **)malloc(sizeof(char *) * (cube->file_len + 1));
    if (!tmp)
        ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
    int j = 0;
    while (cube->map[i])
    {
        tmp[j] = ft_strdup(cube->map[i]);
        i++;
        j++;
    }
    tmp[j] = NULL;
    free(cube->map);
    cube->map = tmp;
}

void    parse_textures(t_cube *cube, int i)
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

static void check_name(int argc, char *s, int i)
{
    if (s == NULL)
        ft_error("Error : No file\n");
    else if (argc > 2)
        ft_error("Error : Too many arguments\n");
    while (s[i])
        i++;
    if (i < 4 || s[i - 1] != 'b' || s[i - 2] != 'u' \
        || s[i - 3] != 'c' || s[i - 4] != '.')
        ft_error("Error : Wrong file extension\n");
    else if (access(s, F_OK) == -1)
        ft_error("Error : File doesn't exist\n");
    else if (access(s, R_OK) == -1)
        ft_error("Error : File is not readable\n");
}

void	is_map_valid(int argc, char *argv[], t_cube *cube)
{
    char *line;
    char *tmp;

    check_name(argc, argv[1], 0);
    cube->fd = open(argv[1], O_RDONLY);
    if (cube->fd == -1)
        ft_error("Error : open failed\n");
    ft_init_texture(cube);
    (1) && (line = get_next_line(cube->fd), tmp = ft_strdup(""));
    while(line)
    {
        cube->file_len++;
        if (line[0] == '\n' || is_an_element(line))
            cube->map_len++;
        tmp = ft_strjoin(tmp, line);
        line = get_next_line(cube->fd);
    }
    cube->fd_file = tmp;
    cube->file = ft_split(tmp, '\n');
    if (!cube->file)
        exit(1);
        // ft_eraser(cube, NULL, (void *)tmp, "Error : ft_split failed\n");
}
