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

static inline int	out_of_bounds(int dir, int cell)
{
	const int	dirs[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	const int	width = get_data()->width;
	const int	height = get_data()->height;

	return ((cell % width == 0 && dirs[dir][0] < 0) || \
				(cell % width == width - 1 && dirs[dir][0] > 0) || \
				(cell < width && dirs[dir][1] < 0) || \
				(cell > width * (height - 1) && dirs[dir][1] > 0));
}

static inline int	next_cell(int dir, int cell)
{
	const int	dirs[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	const int	width = get_data()->width;

	return (cell + dirs[dir][0] + (dirs[dir][1] * width));
}

static int	explore(char *board, int cell, int wall, t_dintarr *area)
{
	int			dir;
	int			next;

	dir = -1;
	board[cell] = wall;
	while (++dir < 4)
	{
		if (out_of_bounds(dir, cell))
			continue ;
		next = next_cell(dir, cell);
		if (board[next] != wall)
			ft_dintarr_add(&area, next);
	}
	return (0);
}

t_dintarr	*floodfill(char *board, t_dintarr *source, int wall,
		size_t max_area)
{
	t_dintarr	*explored;
	char		*copy;
	size_t		i;	

	copy = (char *)xalloc(get_data()->width * get_data()->height);
	if (!copy || !ft_dintarr_create(&explored, 16))
	{
		ft_dintarr_close(&source, NULL);
		return (NULL);
	}
	ft_memcpy(copy, board, get_data()->width * get_data()->height);
	i = 0;
	while (i < source->len)
		explore(copy, source->arr[i++], wall, explored);
	ft_dintarr_close(&source, NULL);
	i = 0;
	while (i < explored->len && i < max_area)
		explore(copy, explored->arr[i++], wall, explored);
	ft_memdel((void **) &copy);
	return (explored);
}
