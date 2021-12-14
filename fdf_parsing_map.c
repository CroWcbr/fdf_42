/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 14:57:14 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/24 17:40:05 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vector	**fdf_dyn_arr_mal_vector(int row, int col)
{
	t_vector	**arr;
	int			i;

	arr = (t_vector **)malloc(row * sizeof(t_vector *));
	if (!arr)
		return ((void *)0);
	i = 0;
	while (i < row)
	{
		arr[i] = (t_vector *)malloc(col * sizeof(t_vector));
		if (arr[i] == (void *)0)
			return ((void *)0);
		i++;
	}
	return (arr);
}

static int	ft_atoi_col_16(const char *str)
{
	int		nbr;
	int		color;
	char	c;

	nbr = 0;
	color = 0;
	while (*str)
	{
		c = ft_toupper(*str);
		if (ft_isdigit(*str))
			nbr = nbr * 16 + *str - '0';
		else
			nbr = nbr * 16 + *str - 'A';
		str++;
	}
	return (nbr);
}

static void	fdf_fill_array(t_map *map, int x, int y, char *num_arr)
{
	char	*temp;

	map->v[y][x].x = x;
	map->v[y][x].y = y;
	map->v[y][x].z = ft_atoi(num_arr);
	map->v[y][x].w = 1;
	if (x == 0 && y == 0)
	{
		map->z_min = map->v[y][x].z;
		map->z_max = map->v[y][x].z;
	}
	map->z_min = ft_min(map->z_min, map->v[y][x].z);
	map->z_max = ft_max(map->z_max, map->v[y][x].z);
	temp = ft_strchr(num_arr, ',');
	if (temp)
	{
		map->v[y][x].colour = ft_atoi_col_16(temp + 3);
		map->colour_map = 1;
	}
	else
		map->v[y][x].colour = WHITE;
}

static int	fdf_map_array(t_list *head, t_map *map)
{
	int		x;
	int		y;
	char	**num_arr;

	map->z_min = 0;
	map->z_max = 0;
	map->colour_map = 0;
	map->v = fdf_dyn_arr_mal_vector(map->row, map->column);
	if (map->v == NULL)
		return (0);
	y = -1;
	while (++y < map->row)
	{
		x = -1;
		num_arr = ft_split(head->content, ' ');
		if (!num_arr)
			return (0);
		while (++x < map->column)
			fdf_fill_array(map, x, y, num_arr[x]);
		ft_free_split(num_arr);
		head = head->next;
	}
	return (1);
}

t_map	*fdf_parsing_map(char *file)
{
	t_map	*map;
	t_list	*head;
	int		fd;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		fdf_error("Error: Wrong malloc t_map");
	map->column = -1;
	map->row = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		fdf_error("Error: map - cannot open file");
	head = fdf_read_map_in_list(fd, map);
	if (!head)
		fdf_error("Error: wrong map");
	if (map->column < 2 || map->row < 2)
		fdf_error("Error: wrong map - not surface");
	if (close(fd) < 0)
		fdf_error("Error: map - cannot close file");
	if (!fdf_map_array(head, map))
		fdf_error("Error: map to array error");
	ft_lstclear(&head, free);
	return (map);
}
