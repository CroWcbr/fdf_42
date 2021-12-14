/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:52:53 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/27 20:31:59 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_vector_on_screen(t_vector v1, t_vector v2, \
									int width, int height)
{
	if (v1.x > 0 && v1.x < width && v2.x > 0 && v2.x < width)
		return (1);
	if (v2.y > 0 && v2.y < height && v2.y > 0 && v2.y < height)
		return (1);
	return (0);
}

static int	choose_color(int data_colour, int v2_colour)
{
	int	colour;

	if (data_colour)
	{
		colour = v2_colour;
	}
	else
		colour = WHITE;
	return (colour);
}

static void	fdf_2_point(t_vector v1, t_vector v2, t_fdf *data)
{
	float	x_step;
	float	y_step;
	int		max;
	int		colour;

	if (!check_vector_on_screen(v1, v2, data->mlx_width, data->mlx_height))
		return ;
	colour = choose_color(data->map->colour_map, v2.colour);
	x_step = v2.x - v1.x;
	y_step = v2.y - v1.y;
	max = ft_max_float(x_step, y_step);
	x_step /= max;
	y_step /= max;
	while (((int)(v1.x - v2.x) || (int)(v1.y - v2.y)))
	{
		if (v1.x > 0 && v1.x < data->mlx_width && \
			v1.y > 0 && v1.y < data->mlx_height)
		{
			data->img.addr[(int)v1.y * data->mlx_width + (int)v1.x] = colour;
			data->check += 1;
		}
		v1.x += x_step;
		v1.y += y_step;
	}
}

static void	check_print(t_fdf *data)
{
	if (data->check < data->map->column || data->check < data->map->row)
	{
		fdf_init_data_default(data);
		fdf_draw(data);
	}
}

void	fdf_draw(t_fdf *data)
{
	int		x;
	int		y;
	float	T[4][4];

	ft_memset(data->img.addr, 0x000000, \
			data->mlx_height * data->mlx_width * sizeof(int));
	fdf_m_m(T, data->Tc, data->Tm);
	data->check = 0;
	y = -1;
	while (++y < data->map->row)
	{
		x = -1;
		while (++x < data->map->column)
		{
			if (x < data->map->column - 1)
				fdf_2_point(fdf_v_m(data->map->v[y][x], T), \
					fdf_v_m(data->map->v[y][x + 1], T), data);
			if (y < data->map->row - 1)
				fdf_2_point(fdf_v_m(data->map->v[y][x], T), \
					fdf_v_m(data->map->v[y + 1][x], T), data);
		}
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	check_print(data);
	print_menu(data);
}
