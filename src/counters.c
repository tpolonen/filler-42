/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:25:18 by tpolonen          #+#    #+#             */
/*   Updated: 2022/12/01 23:25:19 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	count(char *left, char *right, int n)
{
	int ret;

	ret = 0;
	while (n > 0)
	{
		ret += *left & *right;
		left++;
		right++;
		n--;
	}
	return (ret);
}

static int	matches_for_coord(t_coord coord, t_piece *piece, char *board)
{
	const t_data	*data = get_data();
	int				ret;

	ret = count(board + coord.y * data->width + coord.x, piece->ptr,
			piece->width * piece->height);
	return (ret);
}

void	count_board_matches(t_piece *piece, char *board, t_dintarr *out)
{
	const t_data	*data = get_data();
	t_coord			cell;	

	cell.y = 0;
	ft_bzero((void *)board, data->width * data->height);
	while (cell.y < data->height - piece->margin.top - piece->margin.bottom)
	{
		cell.x = 0;
		while (cell.x < data->width && cell.x < data->width - \
				piece->margin.left - piece->margin.right)
		{
			ft_dintarr_add(&out, matches_for_coord(cell, piece, board));
		}
		cell.y++;
	}
}

int	find_juiciest_cell(t_tactics *tactics)
{
	int		hiscore;
	int		best_cell;	
	size_t	i;

	i = 0;
	hiscore = -1;
	best_cell = -1;
	while (i < tactics->juice_scores->len)
	{
		if (tactics->juice_scores->arr[i] > 0 &&
				tactics->juice_scores->arr[i] > hiscore)
		{
			best_cell = tactics->valid_moves->arr[i];
			hiscore = tactics->juice_scores->arr[i];
		}
		i++;
	}
	return (best_cell);
}

int	find_closest_cell(t_tactics *tactics)
{
	int		shortest_dist;
	int		closest_cell;
	size_t	i;

	i = 0;
	shortest_dist = INT_MAX;
	closest_cell = tactics->valid_moves->arr[tactics->valid_moves->len - 1];
	while (i < tactics->distances->len)
	{
		if (tactics->distances->arr[i] < shortest_dist)
		{
			closest_cell = tactics->valid_moves->arr[i];
			shortest_dist = tactics->distances->arr[i];
		}
		i++;
	}
	return (closest_cell);
}
