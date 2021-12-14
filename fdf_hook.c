/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:52:17 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/27 20:31:16 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_close(void)
{	
	exit(0);
}

static void	move_keyboard(float T[4][4], int key, t_fdf *data)
{
	if (key == 123)
		T[0][3] -= 10;
	else if (key == 124)
		T[0][3] += 10;
	else if (key == 125)
		T[1][3] += 10;
	else if (key == 126)
		T[1][3] -= 10;
	fdf_m_m(data->Tc, T, data->Tc);
}

static void	zoom_keyboard(float T[4][4], int key, t_fdf *data)
{
	if (key == 24)
	{
		if (data->zoom_z <= 10)
		{
			T[2][2] *= 1.1;
			data->zoom_z += 1;
		}
	}
	else if (key == 27)
	{
		if (data->zoom_z >= -20)
		{
			T[2][2] *= 0.9;
			data->zoom_z -= 1;
		}	
	}
	fdf_m_m(data->Tm, data->Tm, T);
}

static int	fdf_hook_key(int key, t_fdf *data)
{
	float	T[4][4];

	ft_identity_matrix_4x4(T);
	if (key == 53)
		fdf_close();
	else if (key == 12 || key == 13 || key == 0 || \
			key == 1 || key == 6 || key == 7)
		rotate_keyboard(T, key, data);
	else if (key == 24 || key == 27)
		zoom_keyboard(T, key, data);
	else if (key == 18 || key == 19 || key == 20 || key == 21)
		fdf_choose_projection(data, key);
	else if (key == 123 || key == 124 || key == 125 || key == 126)
		move_keyboard(T, key, data);
	else
		return (0);
	fdf_draw(data);
	return (0);
}

void	fdf_hook(t_fdf *data)
{
	mlx_hook(data->mlx_win, 4, 1L << 2, mouse_press, data);
	mlx_hook(data->mlx_win, 5, 1L << 3, mouse_release, data);
	mlx_hook(data->mlx_win, 6, 1L << 8, mouse_move, data);
	mlx_hook(data->mlx_win, 17, 0, fdf_close, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, fdf_hook_key, data);
}
