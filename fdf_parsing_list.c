/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:07:25 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/24 17:14:40 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_color(char *line)
{
	int	i;

	if (*line != ',' && *(line + 1) != '0' && *(line + 2) != 'x')
		return (0);
	i = 0;
	line += 3;
	while (*line != ' ' && *line)
	{
		if ((*line >= 'a' && *line <= 'f') || \
			(*line >= 'A' && *line <= 'F') || \
			(*line >= '0' && *line <= '9'))
			i++;
		else
			return (0);
		line++;
	}
	if (i > 0 && i <= 6)
		return (1);
	else
		return (0);
}

static int	find_x(char *line)
{
	int	x;

	x = 0;
	while (*line)
	{
		if (*line != ' ' && !ft_isdigit(*line) && *line != '-')
			return (-1);
		while (*line == ' ')
			line++;
		if (*line == '-')
			line++;
		if (ft_isdigit(*line))
			x++;
		while (ft_isdigit(*line))
			line++;
		if (*line == ',')
		{
			if (!check_color(line))
				fdf_error("Error: wrong map - incorrect color");
			while (*line != ' ' && *line)
				line++;
		}
	}
	return (x);
}

static int	check_line_and_find_xy(int gnl, char *line, t_map *map)
{
	int	x;

	if (gnl == -1 || line == ((void *)0))
		return (0);
	if (ft_strlen(line) == 0 && gnl == 0)
		return (1);
	x = find_x(line);
	if (x == -1)
		fdf_error("Error: wrong map - incorrect symbol z");
	if (map->column == -1)
		map->column = x;
	if (map->column != x)
		fdf_error("Error: wrong map - number of column");
	map->row += 1;
	return (1);
}

t_list	*fdf_read_map_in_list(int fd, t_map *map)
{
	int		r;
	char	*line;
	t_list	*tmp;
	t_list	*head;

	r = 1;
	head = NULL;
	line = NULL;
	while (r)
	{
		r = gnl(fd, &line);
		if (!check_line_and_find_xy(r, line, map))
			return (NULL);
		if (ft_strlen(line))
		{
			tmp = ft_lstnew(line);
			if (!tmp)
				return (NULL);
			ft_lstadd_back(&head, tmp);
		}
		else
			free(line);
	}
	return (head);
}
