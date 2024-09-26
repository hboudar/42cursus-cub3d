/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/26 16:06:31 by hboudar          ###   ########.fr       */
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
# define TILE_SIZE 15
# define ROTATION_SPEED 0.06108652382
# define MOVE_SPEED 1
# define FOV 1.0471975511965976
# define FOV_ANGLE 1.0471975512

typedef struct s_player
{
	double	x;
	double	y;
	int		radius; //for draw_circle function in render.c (remove)
	char	direction;
	double	rotation_angle;
	int		facing_up;
	int		facing_down;
	int		facing_left;
	int		facing_right;
	double	true_distance;
	double	vertical_x;
	double	vertical_y;
	double	orizontal_y;
	double	orizontal_x;
}	t_player;

typedef struct s_window
{
	int		*c;
	int		*f;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		flag;
	int		width;
	int		height;
}	t_window;

typedef struct s_parsing
{
	int			fd;
	char		**map;
	char		**file;
	int			map_len;
	char		*fd_file;
	int			len_file;
}	t_parsing;

typedef struct s_cube
{
	void			*mlx;
	mlx_image_t		*image;
	t_player		player;
	t_window		window;
	t_parsing		parsing;
	mlx_texture_t	*wall_1;
	mlx_texture_t	*wall_2;
	mlx_texture_t	*wall_3;
	mlx_texture_t	*wall_4;
	double			ray_intercept;
	double			ray_index;
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
int		skip_line(t_parsing *parsing, int i, int mode);

//execution
void	init_exec(t_cube *cube, t_player *player);
void	execution(void *arg);

//key pressed
void	key_hooks(t_cube *cube, t_player *player, double move_x, double move_y);
void	key_rotations(void *mlx, t_player *player);

//ray casting
void	ray_casting(t_cube *cube, t_player *player);

//render
void	render_map(t_cube *cube, t_player *player, char **map);
void	draw_rays(t_cube *cube, mlx_image_t *image, double angle);

//render utils
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	ft_pixel_to_image(mlx_image_t *image, int x, int y, uint32_t color);
double	normalize_angle(double angle);
void	draw_line(t_cube *cube, int length, int curr_x, int curr_y);

//error
void	ft_eraser(t_cube *cube, void *tmp, int *rgb, char *msg);
int		ft_error(char *msg);

void	render_wall(t_cube *cube, double angle);

#endif
