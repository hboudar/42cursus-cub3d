/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:01:36 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/25 15:07:37 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void    parse_textures(int fd, t_cube *cube)
{
    
}

void    parse_map(int fd, t_cube *cube)
{
    char    *line;
    int     i;

    i = 0;
}

void	is_map_valid(int argc, char *argv[], t_cupe *cube)
{
    int fd;

    check_name(argc, argv[1]);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        write(2, "Error : Can't open the file\n", 29);
        exit (EXIT_FAILURE);
    }
    parse_textures(fd, cube);
    parse_map(fd, cube);
}
