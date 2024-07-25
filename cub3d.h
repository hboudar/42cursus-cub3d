/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/25 14:52:41 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "utils/utils.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>

typedef struct s_cube
{
	void	*mlx_win;
    void	*mlx;
    char    **map;
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    char    *floor;
    char    *ceiling;
}   t_cube;



void	is_map_valid(int argc, char *argv[], t_cupe *cube);

#endif
