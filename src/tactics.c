/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tactics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 17:48:51 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 20:00:35 by tpolonen         ###   ########.fr       */
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

static void	get_values(char *board, t_dintarr *shape, int *values)
{
	size_t	cell_index;
	int		dir;
	int		value;
	int		next;

	cell_index = 0;
	while (cell_index < shape->len)
	{
		dir = -1;
		value = 0;
		while (++dir < 8)
		{
			if (out_of_bounds(dir, shape->arr[cell_index]))
				continue ;
			next = next_cell(dir, shape->arr[cell_index]);
			if (board[next] == 0)
				value++;
		}
		values[cell_index] = value;
		cell_index++;
	}
}

int	get_target(t_data *data, t_strat *strat)
{
	t_dintarr	*shape;
	t_dintarr	*target;
	int			*values;
	int			i;

	if (strat->target)
		ft_memdel((void **)strat->target);
	i = 0;
	while (i < data->width * data->height && strat->enemy[i] == 0)
		i++;
	ft_dintarr_add(&target, i);
	shape = floodfill(strat->enemy, target, 0, SIZE_MAX);
	if (!shape)
	{
		strat->target_count = INT_MIN;
		return (1);
	}
	values = (int *)xalloc(sizeof(int) * shape->len);
	get_values(strat->enemy, shape, values);
	(void)values;
	(void)target;
	return (1);
}
