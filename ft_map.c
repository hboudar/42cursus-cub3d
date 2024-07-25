/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:01:36 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/25 18:28:06 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_init_texture(t_cube *cube)
{
    cube->texture.flag = 0;
    cube->texture.north = NULL;
    cube->texture.south = NULL;
    cube->texture.west = NULL;
    cube->texture.east = NULL;
    // cube->texture.floor[0] = -1;
    // cube->texture.floor[1] = -1;
    // cube->texture.floor[2] = -1;
    // cube->texture.ceiling[0] = -1;
    // cube->texture.ceiling[1] = -1;
    // cube->texture.ceiling[2] = -1;
    
}

static void check_name(int argc, char *str)
{
    int i;

    i = 0;
    if (str == NULL)
    {
        write(2, "Error : No file\n", 16);
        exit (EXIT_FAILURE);
    }
    else if (argc > 2)
    {
        write(2, "Error : Too many arguments\n", 28);
        exit (EXIT_FAILURE);
    }
    while (str[i])
        i++;
    if (i < 4 || str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c' || str[i - 4] != '.')
    {
        write(2, "Error : Wrong file extension\n", 29);
        exit (EXIT_FAILURE);
    }
    else if (access(str, F_OK) == -1)
    {
        write(2, "Error : File doesn't exist\n", 28);
        exit (EXIT_FAILURE);
    }
}

void    parse_textures(t_cube *cube)
{
    int i;
    if (!cube->file)
    {
        write(2, "Error : ft_split failed\n", 25);
        exit (EXIT_FAILURE);
    }
    i = 0;
    while (cube->file[i] && i < 6)
    {
        if (cube->file[i][0] == 'N' && cube->file[i][1] == 'O' && cube->file[i][2] == ' ')
            cube->texture.north = get_element(cube->file[i], &cube->texture.flag);
        else if (cube->file[i][0] == 'S' && cube->file[i][1] == 'O' && cube->file[i][2] == ' ')
            cube->texture.south = get_element(cube->file[i], &cube->texture.flag);
        else if (cube->file[i][0] == 'W' && cube->file[i][1] == 'E' && cube->file[i][2] == ' ')
            cube->texture.west = get_element(cube->file[i], &cube->texture.flag);
        else if (cube->file[i][0] == 'E' && cube->file[i][1] == 'A' && cube->file[i][2] == ' ')
            cube->texture.east = get_element(cube->file[i], &cube->texture.flag);
        else if (cube->file[i][0] == 'F' && cube->file[i][1] == ' ')
            getelement2(cube->file[i], &cube->texture.flag);
        else if (cube->file[i][0] == 'C' && cube->file[i][1] == ' ')
            getelement2(cube->file[i], &cube->texture.flag);
        i++;
    }
    // print_file(cube);
}


void	is_map_valid(int argc, char *argv[], t_cube *cube)
{
    char *line;
    char *tmp;

    check_name(argc, argv[1]);
    cube->fd = open(argv[1], O_RDONLY);
    if (cube->fd == -1)
    {
        write(2, "Error : Can't open the file\n", 29);
        exit (EXIT_FAILURE);
    }
    ft_init_texture(cube);
    line = get_next_line(cube->fd);
    tmp = ft_strdup("");
    while(line)
    {
        tmp = ft_strjoin(tmp, line);
        line = get_next_line(cube->fd);
    }
    cube->file = ft_split(tmp, '\n');
    free(tmp);
    parse_textures(cube);
}
