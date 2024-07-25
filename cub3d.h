/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/25 18:26:31 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./lib/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>

typedef struct s_texture
{
    int     flag;
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     *floor;
    int     *ceiling;
}   t_texture;

typedef struct s_cube
{
	void	*mlx_win;
    void	*mlx;
    char    **file;
    char    **map;
    t_texture texture;
    int     fd;
}   t_cube;



void	is_map_valid(int argc, char *argv[], t_cube *cube);
void	print_file(t_cube *cube);


#endif
