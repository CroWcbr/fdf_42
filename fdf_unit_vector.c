/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_unit_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:47:23 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/25 16:54:24 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_identity_matrix_4x4(float T[4][4])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (i == j)
				T[i][j] = 1;
			else
				T[i][j] = 0;
		}
	}
}

t_vector	fdf_v_m(t_vector tmp, float m[4][4])
{
	t_vector	v;

	v.x = tmp.x * m[0][0] + tmp.y * m[0][1] + tmp.z * m[0][2] + tmp.w * m[0][3];
	v.y = tmp.x * m[1][0] + tmp.y * m[1][1] + tmp.z * m[1][2] + tmp.w * m[1][3];
	v.z = tmp.x * m[2][0] + tmp.y * m[2][1] + tmp.z * m[2][2] + tmp.w * m[2][3];
	v.w = tmp.x * m[3][0] + tmp.y * m[3][1] + tmp.z * m[3][2] + tmp.w * m[3][3];
	v.colour = tmp.colour;
	return (v);
}

void	fdf_m_m(float T[4][4], float m[4][4], float mm[4][4])
{
	float	tmp[4][4];
	int		i;
	int		j;
	int		r;

	ft_bzero(tmp, 16 * sizeof(tmp[0][0]));
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			r = -1;
			while (++r < 4)
				tmp[i][j] += m[i][r] * mm[r][j];
		}
	}
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			T[i][j] = tmp[i][j];
	}
}
