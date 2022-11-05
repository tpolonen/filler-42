/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tactics.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 17:48:51 by tpolonen          #+#    #+#             */
/*   Updated: 2022/11/04 15:34:20 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static inline int	out_of_bounds(int dir, int cell)
{
	const int	dirs[8][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}, \
				{1, -1}, {1, 1}, {-1, 1}, {-1, -1}};
	const int	width = get_data()->width;
	const int	height = get_data()->height;

	return ((cell % width == 0 && dirs[dir][0] < 0) || \
				(cell % width == width - 1 && dirs[dir][0] > 0) || \
				(cell < width && dirs[dir][1] < 0) || \
				(cell > width * (height - 1) && dirs[dir][1] > 0));
}

static inline int	next_cell(int dir, int cell)
{
	const int	dirs[8][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}, \
				{1, -1}, {1, 1}, {-1, 1}, {-1, -1}};
	const int	width = get_data()->width;

	return (cell + dirs[dir][0] + (dirs[dir][1] * width));
}

static int	*get_values(char *board, t_dintarr *shape)
{
	size_t	cell_index;
	int		*values;
	int		dir;
	int		value;
	int		next;

	cell_index = 0;
	values = xalloc(sizeof(int) * shape->len);
	while (values && cell_index < shape->len)
	{
		dir = -1;
		value = 0;
		while (++dir < 8)
		{
			if (out_of_bounds(dir, shape->arr[cell_index]))
				continue ;
			next = next_cell(dir, shape->arr[cell_index]);
			if (board[next] == 1)
				value++;
		}
		values[cell_index++] = value;
	}
	return (values);
}

static t_dintarr	*get_source(char *board, t_dintarr *shape)
{
	t_dintarr	*source;
	int			*values;
	int			max;
	int			i;

	values = get_values(board, shape);
	max = -1;
	i = 0;
	while ((size_t) i < shape->len)
	{
		if (values[i] > max)
			max = values[i];
		i++;
	}
	while (i > 0)
	{
		if (values[i] == max)
			ft_dintarr_add(&source, shape->arr[i]);
		i++;
	}
	return (source);
}

int	get_new_target(t_strat *strat)
{
	t_dintarr	*shape;
	t_dintarr	*source;
	int			i;

	if (strat->target)
		ft_memdel((void **)strat->target);
	i = 0;
	while (strat->enemy[i++] == 0)
		;
	ft_dintarr_add(&source, i);
	shape = floodfill(strat->enemy, source, 0, SIZE_MAX);
	if (!shape)
		return (INT_MIN);
	source = get_source(strat->enemy, shape);
	strat->target = floodfill(strat->enemy, source, 1, 50);
	return (strat->target->len);
}
