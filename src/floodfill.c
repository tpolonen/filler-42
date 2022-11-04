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

static int	explore(char *board, int cell, int wall, t_dintarr *area)
{
	const int	dirs[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	int			i;
	int			next_cell;
	int			width;

	i = -1;
	width = get_data()->width;
	board[cell] = wall;
	while (++i < 4)
	{
		if (out_of_bounds(i, cell))
			continue ;
		next_cell = cell + dirs[i][0] + (dirs[i][1] * width);
		if (board[next_cell] != wall)
			ft_dintarr_add(&area, next_cell);
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
