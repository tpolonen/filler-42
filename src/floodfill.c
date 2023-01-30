/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:57:33 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 20:00:35 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdio.h>

static inline int	out_of_bounds(int dir, int cell, int width, int height)
{
	const int	dirs[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

	return ((cell % width == 0 && dirs[dir][0] < 0) || \
				(cell % width == width - 1 && dirs[dir][0] > 0) || \
				(cell < width && dirs[dir][1] < 0) || \
				(cell > width * (height - 1) && dirs[dir][1] > 0));
}

static inline int	next_cell(int dir, int cell, int width)
{
	const int	dirs[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

	return (cell + dirs[dir][0] + (dirs[dir][1] * width));
}

static void	explore(char *board, int cell, int wall, t_dintarr *area)
{
	int			dir;
	int			next;
	const int	width = get_data()->width;
	const int	height = get_data()->height;

	dir = -1;
	while (++dir < 4)
	{
		next = next_cell(dir, cell, width);
		if (next >= width * height || out_of_bounds(dir, cell, width, height))
			continue ;
		if (board[next] != wall)
		{
			board[next] = wall;
			ft_dintarr_add(&area, next);
		}
	}
}

void	floodfill(t_tactics *tactics, t_strat *strat, char *board,
		size_t max_area)
{
	const t_data	*data = get_data();
	char			*copy;
	int				wall;
	size_t			i;

	copy = (char *)xalloc(data->width * data->height);
	if (!copy)
		return ;
	wall = board[tactics->source->arr[0]];
	ft_memcpy(copy, board, data->width * data->height);
	i = 0;
	while (i < tactics->source->len)
		explore(copy, tactics->source->arr[i++], wall, strat->target_shape);
	i = 0;
	while (i < strat->target_shape->len && strat->target_shape->len < max_area)
		explore(copy, strat->target_shape->arr[i++], wall, strat->target_shape);
	ft_memdel((void **) &copy);
}
