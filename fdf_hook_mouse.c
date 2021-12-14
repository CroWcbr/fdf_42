/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:23:57 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/27 21:02:22 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_mouse(t_fdf *data, int up, int down)
{
	float	T[4][4];

	ft_identity_matrix_4x4(T);
	if (up)
	{
		if (data->zoom <= 10)
		{
			T[0][0] = 1.1;
			T[1][1] = 1.1;
			T[2][2] = 1.1;
			data->zoom += 1;
		}
	}
	else if (down)
	{
		if (data->zoom >= -20)
		{
			T[0][0] = 0.9;
			T[1][1] = 0.9;
			T[2][2] = 0.9;
			data->zoom -= 1;
		}	
	}
	fdf_m_m(data->Tm, T, data->Tm);
	fdf_draw(data);
}

int	mouse_press(int button, int x, int y, t_fdf *data)
{
	if (button == 1)
	{
		data->mouse.is_pres = 1;
		data->mouse.pr_x = x;
		data->mouse.pr_y = y;
	}
	else if (button == 4)
		scale_mouse(data, 1, 0);
	else if (button == 5)
		scale_mouse(data, 0, 1);
	return (0);
}

int	mouse_release(int button, int x, int y, t_fdf *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		data->mouse.is_pres = 0;
	return (0);
}

int	mouse_move(int x, int y, t_fdf *data)
{
	float	T[4][4];
	float	dx;
	float	dy;

	ft_identity_matrix_4x4(T);
	if (data->mouse.is_pres == 1 && (ft_abs(data->mouse.pr_x - x) > 10 || \
			ft_abs(data->mouse.pr_y - y) > 10))
	{
		dy = 0;
		dx = 0;
		if (ft_abs(data->mouse.pr_x - x) > 10)
		{
			dy = (data->mouse.pr_x - x);
			data->mouse.pr_x = x;
		}
		else
		{
			dx = (data->mouse.pr_y - y);
			data->mouse.pr_y = y;
		}
		rotate_mouse(T, dx, -dy);
		fdf_m_m(data->Tm, T, data->Tm);
		fdf_draw(data);
	}
	return (0);
}
