/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 14:14:16 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/30 20:08:33 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/include/libft.h"
# include "./minilibx_macos/mlx.h"
# include <stdlib.h>
# include <errno.h>
# include <math.h>

# define WHITE 0xffffff
# define PI 3.14159265358979323846

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
	float	w;
	int		colour;
}t_vector;

typedef struct s_map
{
	int			column;
	int			row;
	int			z_min;
	int			z_max;
	int			colour_map;
	t_vector	**v;
}t_map;

typedef struct s_data {
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;

typedef struct s_mouse
{
	int	is_pres;
	int	x;
	int	y;
	int	pr_x;
	int	pr_y;
}t_mouse;

typedef struct s_fdf
{
	t_map	*map;
	void	*mlx;
	void	*mlx_win;
	int		mlx_width;
	int		mlx_height;
	t_data	img;
	t_mouse	mouse;
	float	Tc[4][4];
	float	Tm[4][4];
	int		check;
	int		zoom;
	int		zoom_z;
}t_fdf;

//pars
t_map		*fdf_parsing_map(char *file);
t_list		*fdf_read_map_in_list(int fd, t_map *map);

//draw
void		fdf_draw(t_fdf *data);
void		print_menu(t_fdf *data);

//init
void		fdf_init_data_default(t_fdf *data);

//vector
t_vector	fdf_v_m(t_vector tmp, float m[4][4]);
void		fdf_m_m(float T[4][4], float m[4][4], float mm[4][4]);
void		ft_identity_matrix_4x4(float T[4][4]);

//hook
void		fdf_hook(t_fdf *data);
void		scale_mouse(t_fdf *data, int up, int down);
int			mouse_press(int button, int x, int y, t_fdf *data);
int			mouse_release(int button, int x, int y, t_fdf *data);
int			mouse_move(int x, int y, t_fdf *data);
void		fdf_choose_projection(t_fdf *data, int key);
void		rotate_mouse(float T[4][4], int dx, int dy);
void		rotate_keyboard(float T[4][4], int key, t_fdf *data);

//libft
int			ft_max(int x, int y);
int			ft_min(int x, int y);
int			ft_abs(int j);
void		fdf_error(char *s);
float		ft_max_float(float x, float y);

//help_print
void		print_parsing(t_map *map);
void		print_parsing_map(t_map *map);
void		fdf_print_map_T(float T[4][4], char *str);

#endif