/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/23 09:52:52 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>//remove
# include <fcntl.h>
# include <unistd.h>
# include "../_Utils/libft.h"
# include "../../../MLX42/include/MLX42/MLX42.h"

# define WIDTH 1000
# define HEIGHT 600
# define TILE_SIZE 60
# define ROTATION_SPEED 3.5
# define DEG_TO_RAD
# define MOVE_SPEED 3.5

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

typedef struct s_player
{
	char	player;
	double	x;
	double	y;
	int		radius;//radius 3
	double	turn_direction;//turn direction 0     //left -1 right +1
	double	walk_direction;//walk direction 0     //back -1 front +1
	double	rotation_angle;//rotation angle math.pi/2
	double	move_speed;//move speed 3.0
	double	rotation_speed;//rotation speed 3 * (math.pi / 180)
}	t_player;

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
	int			height;
	int			width;
	int			fd;
	t_texture	texture;
	t_player	player;
}	t_cube;

//parsing
void	is_map_valid(int argc, char *argv[], t_cube *cube);

//parsing utils
void	check_map_name(int argc, char *name, int i);
void	initialize_list(t_cube *cube, char *map);
int		check_elem(char **map, t_cube *cube);
void	get_element(t_cube *cube, char *str, char mode);
int		check_map(char **map, int x, int y);
int		skip_space(char *str, int mode);
int		skip_line(t_cube *cube, int i, int mode);

//execution
void	execution(void *arg);

//render
void	render_map(t_cube *cube, t_player *player, char **map);

//render utils
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	check_move(t_cube *cube, double move_x, double move_y);
void	ft_pixel_to_image(mlx_image_t *image, int x, int y, uint32_t color);

//error
void	ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg);
int		ft_error(char *msg);

#endif
