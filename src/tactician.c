/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tactician.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 17:48:51 by tpolonen          #+#    #+#             */
/*   Updated: 2023/01/14 19:32:48 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static inline int	out_of_bounds(int dir, int cell, int width, int height)
{
	const int	dirs[8][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}, \
				{1, -1}, {1, 1}, {-1, 1}, {-1, -1}};

	return ((cell % width == 0 && dirs[dir][0] < 0) || \
				(cell % width == width - 1 && dirs[dir][0] > 0) || \
				(cell < width && dirs[dir][1] < 0) || \
				(cell > width * (height - 1) && dirs[dir][1] > 0));
}

static inline int	next_cell(int dir, int cell, int width)
{
	const int	dirs[8][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}, \
				{1, -1}, {1, 1}, {-1, 1}, {-1, -1}};

	return (cell + dirs[dir][0] + (dirs[dir][1] * width));
}

static void	find_source(int *values, t_dintarr *shape, t_dintarr *source)
{
	int			max;
	int			i;

	max = -1;
	i = 0;
	while ((size_t) i < shape->len)
	{
		if (values[i] > max)
			max = values[i];
		i++;
	}
	i = 0;
	while ((size_t) i < shape->len)
	{
		if (values[i] == max)
			ft_dintarr_add(&source, shape->arr[i]);
		i++;
	}
}

void	find_values(t_dintarr *shape)
{
	const t_data	*data = get_data();
	size_t			cell_index;
	int				*values;
	int				dir;
	int				value;

	cell_index = 0;
	values = get_strat()->values_arr;
	while (cell_index < shape->len)
	{
		dir = -1;
		value = 0;
		while (++dir < 8)
		{
			if (out_of_bounds(dir, \
						shape->arr[cell_index], data->width, data->height))
				continue ;
			if (!data->xoboard_ptr[\
					next_cell(dir, shape->arr[cell_index], data->width)])
				value++;
		}
		values[cell_index++] = value;
	}
}

void	find_new_target(t_strat *strat)
{
	const t_data	*data = get_data();
	t_dintarr		*source;
	t_dintarr		*enemy_shape;
	size_t			i;

	if (!ft_dintarr_clear(&strat->target_shape))
		ft_dintarr_create(&strat->target_shape, 8);
	enemy_shape = get_enemy_shape();
	ft_memdel((void **)&strat->values_arr);
	strat->values_arr = (int *)xalloc(sizeof(int) * enemy_shape->len);
	find_values(enemy_shape);
	source = get_tactics()->source;
	if (!ft_dintarr_clear(&source))
		ft_dintarr_create(&source, 8);
	find_source(strat->values_arr, enemy_shape, source);
	strat->target_shape = floodfill(&source, data->xoboard_ptr, 1, \
			ft_max(50, strat->free_space / 3));
	ft_memdel((void **)strat->target_ptr);
	strat->target_ptr = (char *)xalloc(data->width * data->height);
	i = 0;
	while (i < strat->target_shape->len)
		strat->target_ptr[strat->target_shape->arr[i++]] = 1;
}
