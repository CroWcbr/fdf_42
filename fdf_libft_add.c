/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_libft_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:53:25 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/25 21:55:03 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_max(int x, int y)
{
	if (x < y)
		return (y);
	return (x);
}

int	ft_min(int x, int y)
{
	if (x > y)
		return (y);
	return (x);
}

int	ft_abs(int j)
{
	if (j < 0)
		return (-j);
	return (j);
}

void	fdf_error(char *s)
{
	write(2, s, ft_strlen(s));
	ft_putstr_fd("\n", 2);
	exit(1);
}

float	ft_max_float(float x, float y)
{
	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;
	if (x < y)
		return (y);
	else
		return (x);
}
