/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:47:52 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/27 00:15:26 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	rotate_x(float T[4][4], int x_angle)
{
	T[1][1] = cos(x_angle * PI / 180);
	T[1][2] = -sin(x_angle * PI / 180);
	T[2][2] = cos(x_angle * PI / 180);
	T[2][1] = sin(x_angle * PI / 180);
}

static	void	rotate_y(float T[4][4], int y_angle)
{
	T[0][0] = cos(y_angle * PI / 180);
	T[0][2] = sin(y_angle * PI / 180);
	T[2][0] = -sin(y_angle * PI / 180);
	T[2][2] = cos(y_angle * PI / 180);
}

static	void	rotate_z(float T[4][4], int z_angle)
{
	T[0][0] = cos(z_angle * PI / 180);
	T[0][1] = -sin(z_angle * PI / 180);
	T[1][0] = sin(z_angle * PI / 180);
	T[1][1] = cos(z_angle * PI / 180);
}

void	rotate_mouse(float T[4][4], int dx, int dy)
{
	if (dx)
		rotate_x(T, dx);
	else
		rotate_y(T, dy);
}

void	rotate_keyboard(float T[4][4], int key, t_fdf *data)
{
	if (key == 12)
		rotate_x(T, -10);
	else if (key == 13)
		rotate_x(T, 10);
	else if (key == 0)
		rotate_y(T, -10);
	else if (key == 1)
		rotate_y(T, 10);
	else if (key == 6)
		rotate_z(T, -10);
	else if (key == 7)
		rotate_z(T, 10);
	fdf_m_m(data->Tm, T, data->Tm);
}
