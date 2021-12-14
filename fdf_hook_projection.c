/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:45:07 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/27 21:04:49 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init_data_default(t_fdf *data)
{
	int		zoom;
	float	T[4][4];

	ft_identity_matrix_4x4(data->Tm);
	data->Tm[0][3] -= data->map->column / 2;
	data->Tm[1][3] -= data->map->row / 2;
	ft_identity_matrix_4x4(data->Tc);
	data->Tc[0][3] = data->mlx_width / 2;
	data->Tc[1][3] = data->mlx_height / 2;
	zoom = ft_min(data->mlx_width / 2 / data->map->column, \
					data->mlx_height / 2 / data->map->row);
	if (zoom <= 0)
		zoom = 1;
	ft_identity_matrix_4x4(T);
	T[0][0] = zoom;
	T[1][1] = zoom;
	T[2][2] = zoom;
	fdf_m_m(data->Tm, T, data->Tm);
	data->zoom = 0;
	data->zoom_z = 0;
}

static void	fdf_init_data_iso(t_fdf *data)
{
	float	T[4][4];

	fdf_init_data_default(data);
	ft_identity_matrix_4x4(T);
	T[0][0] = cos(45 * PI / 180);
	T[0][1] = -sin(45 * PI / 180);
	T[1][0] = sin(45 * PI / 180);
	T[1][1] = cos(45 * PI / 180);
	fdf_m_m(data->Tm, T, data->Tm);
	ft_identity_matrix_4x4(T);
	T[1][1] = cos(35 * PI / 180);
	T[1][2] = -sin(35 * PI / 180);
	T[2][2] = cos(35 * PI / 180);
	T[2][1] = sin(35 * PI / 180);
	fdf_m_m(data->Tm, T, data->Tm);
	data->zoom = 0;
	data->zoom_z = 0;
}

static void	fdf_init_data_paralel(t_fdf *data)
{
	float	T[4][4];

	ft_identity_matrix_4x4(T);
	T[2][2] = 0;
	fdf_m_m(data->Tm, T, data->Tm);
}

static void	fdf_change_colour(t_fdf *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map->row)
	{
		x = -1;
		while (++x < data->map->column)
		{
			if (data->map->v[y][x].z <= 0)
				data->map->v[y][x].colour = 0x0000FF;
			else
				data->map->v[y][x].colour = 0x00FF00;
			if (x > 0 && data->map->v[y][x].z < data->map->v[y][x - 1].z)
				data->map->v[y][x].colour = data->map->v[y][x - 1].colour;
			if (y > 0 && data->map->v[y][x].z < data->map->v[y - 1][x].z)
				data->map->v[y][x].colour = data->map->v[y - 1][x].colour;
		}	
	}
	data->map->colour_map = 1;
}

void	fdf_choose_projection(t_fdf *data, int key)
{
	if (key == 18)
		fdf_init_data_default(data);
	else if (key == 19)
		fdf_init_data_iso(data);
	else if (key == 20)
		fdf_init_data_paralel(data);
	else if (key == 21)
		fdf_change_colour(data);
}
