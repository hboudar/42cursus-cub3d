/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/24 16:04:02 by hboudar          ###   ########.fr       */
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
# define ROTATION_SPEED 0.06108652382
# define MOVE_SPEED 3.5
# define FOV 1.0471975511965976
# define FOV_ANGLE 1.0471975512

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
	int		radius;
	double	x;
	double	y;
	double	turn_direction;
	double	walk_direction;
	double	rotation_angle;
	double	horizontal_x;
	double	horizontal_y;
	double	vertical_x;
	double	vertical_y;
}	t_player;

typedef struct s_cube
{
	int			facing_down;
	int			facing_up;
	int			facing_right;
	int			facing_left;
	double		true_distance;
	double		orizontal_position_x;
	double		orizontal_position_y;
	double		vertical_position_x;
	double		vertical_position_y;
	int			columx;
	int			columy;
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
void	init_exec(t_cube *cube, t_player *player);
void	execution(void *arg);

//key pressed
void	key_hooks(t_cube *cube, t_player *player, double move_x, double move_y);
void	key_rotations(void *mlx, t_player *player);

//ray casting
void	ray_casting(t_cube *cube);

//render
void	render_map(t_cube *cube, t_player *player, char **map);
void	draw_rays(t_cube *cube, mlx_image_t *image, double angle);

//render utils
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	ft_pixel_to_image(mlx_image_t *image, int x, int y, uint32_t color);
double	normalize_angle(double angle);
void	draw_line(t_cube *cube, int length, int curr_x, int curr_y);

//error
void	ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg);
int		ft_error(char *msg);

#endif
