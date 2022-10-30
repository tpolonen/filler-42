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

static int	explore(char *board, int cell, int filled, t_dintarr *explored)
{
	const int 	dirs[4][2]  = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	int			i;
	int			next_cell;
	int			width;

	i = 0;
	width = get_data()->width;
	while (i < 4)
	{
		if (cell % width == 0 && dirs[i][0] < 0)
			continue;
		if (cell % width == width - 1 && dirs[i][0] > 0)
			continue;
		next_cell = cell + dirs[i][0] + (dirs[i][1] * get_data()->width);
	}
	return (0);
}

t_dintarr	*floodfill(char *board, int *source, size_t size, size_t steps)
{
	t_dintarr	*explored;
	int			filled;
	char		*copy;

	copy =(char *)xalloc(get_data()->width * get_data()->height);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, board, get_data()->width * get_data()->height);
	if (!ft_dintarr_create(&explored, 16))
		return (NULL);
	filled = board[source[0]];
	while (size-- > 0)
		explore(copy, source[size], filled, explored);
	(void)steps;

	return (explored);
}
