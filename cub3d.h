/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/06 15:53:55 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./utils/libft.h"
# include <stdio.h> //to be removed
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

typedef struct s_texture
{
    int     flag;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     *f;
    int     *c;
}   t_texture;

typedef struct s_cube
{
	void	*mlx_win;
    void	*mlx;
    char    **file;
    char    **map;
    char    *fd_file;
    int     map_len;
    int     file_len;
    t_texture texture;
    int     height;
    int     width;
    int     fd;
}   t_cube;


//parsing functions
void    is_map_valid(int argc, char *argv[], t_cube *cube);
void    parse_textures(t_cube *cube, int i);
void    parse_map(t_cube *cube, char *tmp1, char **tmp2, int i);

void    check_map_name(int argc, char *name, int i);
void    initialize_list(t_cube *cube, char *map);
int     skip_space(char *str);

int     parse_mape2(t_cube *cube);


//utils
void    get_element(t_cube *cube, char *str, char mode);
void    ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg);
void    take_map(t_cube *cube, int i, int j, int k);
void    ft_error(char *msg);

//tmp
void	print_file(t_cube *cube);

#endif
