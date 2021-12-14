/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 13:51:28 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/01 17:49:07 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_fdf	*fdf_init_data(void)
{
	t_fdf	*data;

	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!data)
		fdf_error("Error: Wrong malloc t_fdf");
	data->mlx_width = 1920;
	data->mlx_height = 1280;
	data->zoom = 0;
	data->zoom_z = 0;
	return (data);
}

int	main(int argc, char **argv)
{
	t_fdf	*data;

	if (argc != 2)
		fdf_error("Error: Wrong enter");
	data = fdf_init_data();
	data->map = fdf_parsing_map(argv[1]);
	fdf_init_data_default(data);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, \
			data->mlx_width, data->mlx_height, "FDF");
	data->img.img = mlx_new_image(data->mlx, \
			data->mlx_width, data->mlx_height);
	data->img.addr = (int *)mlx_get_data_addr(data->img.img, \
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	fdf_draw(data);
	fdf_hook(data);
	mlx_loop(data->mlx);
	return (0);
}
