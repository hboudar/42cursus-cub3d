/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/16 09:33:38 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../_Utils/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../../../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

# define WIDTH 1000
# define HEIGHT 600
# define TILE_SIZE 25

typedef struct s_texture
{
	int		flag;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*f;
	int		*c;
}	t_texture;

typedef struct s_vector
{
	int		x_map;
	int		y_map;
}	t_vector;

typedef struct s_cube
{
	char		**map;
	int			map_len;
	void		*mlx;
	void		*mlx_win;
	void		*mlx_img;
	mlx_image_t	*image;
	char		**file;
	int			len_file;
	char		*fd_file;
	uint32_t	height;
	uint32_t	width;
	int			fd;
	t_texture	texture;
	t_vector	player;
}	t_cube;

void	is_map_valid(int argc, char *argv[], t_cube *cube);//parsing

void	check_map_name(int argc, char *name, int i);//parsing utils
void	initialize_list(t_cube *cube, char *map);//parsing utils
int		check_elem(char **map, t_cube *cube);
void	get_element(t_cube *cube, char *str, char mode);//parsing utils
int		check_map(char **map, int x, int y);//parsing utils
int		skip_space(char *str);//parsing utils
int		just_space(char *str);//parsing utils
int		skip_line(t_cube *cube, int i, int mode);//parsing utils

void	ft_render(void *arg);//render

void	ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg);//error
int		ft_error(char *msg);//error

#endif
