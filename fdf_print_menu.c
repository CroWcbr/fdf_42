/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_print_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:55:16 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/27 20:55:31 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_menu(t_fdf *data)
{
	char	*menu;
	int		colour;

	colour = 0x0000FF;
	menu = "Q/W/A/S/Z/X - rotation X/Y/Z";
	mlx_string_put(data->mlx, data->mlx_win, 10, 15, colour, menu);
	menu = "BUTTON 1 - rotation mouse";
	mlx_string_put(data->mlx, data->mlx_win, 10, 30, colour, menu);
	menu = "SCROLL BAR - zoom, +/- zoom only z";
	mlx_string_put(data->mlx, data->mlx_win, 10, 45, colour, menu);
	menu = "UP/DOWN/LEFT/RIGHT - move";
	mlx_string_put(data->mlx, data->mlx_win, 10, 60, colour, menu);
	menu = "1, 2, 3 - def, iso, paralel projection";
	mlx_string_put(data->mlx, data->mlx_win, 10, 75, colour, menu);
	menu = "4 - simple colour";
	mlx_string_put(data->mlx, data->mlx_win, 10, 90, colour, menu);
}
