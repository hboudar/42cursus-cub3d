/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/08 17:05:53 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./utils/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

# define WIDTH 800
# define HEIGHT 600

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

typedef struct s_cube
{
	char		**map;
	int			map_len;
	void		*mlx;
	void		*mlx_win;
	void		*mlx_img;
	mlx_image_t			*image;
	char		**file;
	int			len_file;
	char		*fd_file;
	int			height;
	int			width;
	int			fd;
	t_texture	texture;
}	t_cube;

void	is_map_valid(int argc, char *argv[], t_cube *cube);//parsing
void	parse_textures(t_cube *cube, int i);//parsing
void	parse_map(t_cube *cube, char *tmp1, char **tmp2, int i);//parsing
int		parse_mape2(t_cube *cube);//parsing

void	initialize_list(t_cube *cube, char *map);//parsing utils
void	check_map_name(int argc, char *name, int i);//parsing utils
void	get_element(t_cube *cube, char *str, char mode);//parsing utils
void	take_map(t_cube *cube, int i, int j, int k);//parsing utils
int		skip_space(char *str);//parsing utils

void	ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg);//utils
void	ft_error(char *msg);//utils

#endif
