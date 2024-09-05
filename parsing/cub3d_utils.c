/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:43:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/05 13:38:52 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int    costum_atoi(char *str, int *index)
{
    int res;
    int i;

    i = 0;
    res = 0;
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

static int    *get_rgb(t_cube *cube, char **tmp)
{
    int f;
    int j;
    int i;
    int *rgb;

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
    return (rgb);
}

void    get_element(t_cube *cube, char *str, char mode)
{
    int i;
    char **tmp;

    i = 0;
    tmp = ft_split(str, ' ');
    if (!tmp)
        ft_eraser(cube, NULL, NULL, "Error : ft_split failed 1\n");
    if (tmp[0] != NULL && tmp[1] != NULL && tmp[2] == NULL)
    {
        (mode == 'N') && (cube->texture.no = ft_strdup(tmp[1]));
        (mode == 'S') && (cube->texture.so = ft_strdup(tmp[1]));
        (mode == 'W') && (cube->texture.we = ft_strdup(tmp[1]));
        (mode == 'E') && (cube->texture.ea = ft_strdup(tmp[1]));
        (mode == 'F') && (cube->texture.f = get_rgb(cube, tmp));
        (mode == 'C') && (cube->texture.c = get_rgb(cube, tmp));
        cube->texture.flag++;
    }
    else
        ft_eraser(cube, tmp, NULL, "Error : Wrong format\n");
    while (tmp[i])
        free(tmp[i++]);
    free(tmp);
}

void    initialize_list(t_cube *cube, char *map)
{
    cube->fd = open(map, O_RDONLY);
    if (cube->fd == -1)
        ft_error("Error : open failed\n");
    cube->map_len = 0;
    cube->file_len = 0;
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
    
}

void check_map_name(int argc, char *name, int i)
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

void    get_element_test_version(t_cube *cube, char *element)
{
    char *tmp = NULL;
    int *tmp2 = NULL;

    if (element[0] == 'N' && element[1] == 'O')
        tmp = ft_substr(element, 3, ft_strlen(element) - 3);
    else if (element[0] == 'S' && element[1] == 'O')
        tmp = ft_substr(element, 3, ft_strlen(element) - 3);
    else if (element[0] == 'W' && element[1] == 'E')
        tmp = ft_substr(element, 3, ft_strlen(element) - 3);
    else if (element[0] == 'E' && element[1] == 'A')
        tmp = ft_substr(element, 3, ft_strlen(element) - 3);
    else if (element[0] == 'F')
        tmp2 = get_rgb(cube, ft_split(element, ' '));
    else if (element[0] == 'C')
        tmp2 = get_rgb(cube, ft_split(element, ' '));
    if (element[0] == 'F' || element[0] == 'C')
        printf ("tmp2 : {%d, %d, %d}\n", tmp2[0], tmp2[1], tmp2[2]);
    else
        printf ("tmp : {%s}\n", tmp);
}
