/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:25:18 by tpolonen          #+#    #+#             */
/*   Updated: 2023/01/31 19:06:31 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	count(char *left, char *right, int n)
{
	int	ret;

	ret = 0;
	while (n-- > 0)
	{
		ret += *left & *right;
		left++;
		right++;
	}
	return (ret);
}

static int	matches_for_coord(t_coord *coord, t_piece *piece, char *board)
{
	const t_data	*data = get_data();
	int				cell_to_start;
	int				check_size;
	int				ret;

	cell_to_start = coord->x + (coord->y * data->width);
	check_size = ft_min(data->width * (piece->rect.y2 - piece->rect.y1 + 1),
			(data->width * data->height) - cell_to_start);
	ret = count(board + cell_to_start, piece->ptr, check_size);
	return (ret);
}

void	count_board_matches(t_piece *piece, char *board, t_dintarr *out)
{
	const t_data	*data = get_data();
	t_coord			cell;	

	cell.y = 0;
	while (cell.y < data->height - (piece->rect.y2 - piece->rect.y1))
	{
		cell.x = 0;
		while (cell.x < data->width - (piece->rect.x2 - piece->rect.x1))
		{
			ft_dintarr_add(&out, matches_for_coord(&cell, piece, board));
			cell.x++;
		}
		while (cell.x < data->width)
		{
			ft_dintarr_add(&out, 0);
			cell.x++;
		}
		cell.y++;
	}
	while (cell.y < data->height)
	{
		ft_dintarr_add(&out, 0);
		cell.y++;
	}
}

int	find_juiciest_cell(t_tactics *tactics)
{
	int		hiscore;
	int		best_cell;	
	int		i;
	int		hit;

	i = 0;
	hit = 0;
	hiscore = -1;
	best_cell = -1;
	while (i < (int)tactics->juice_scores->len)
	{
		if (tactics->juice_scores->arr[i] > 0 && \
			tactics->juice_scores->arr[i] > hiscore)
		{
			best_cell = tactics->valid_moves->arr[i];
			hiscore = tactics->juice_scores->arr[i];
			hit = i;
		}
		i++;
	}
	if (DEBUG && best_cell >= 0)
		print_debug_choice(hit, hiscore, "juiciness");
	return (best_cell);
}

int	find_closest_cell(t_tactics *tactics)
{
	int		shortest_dist;
	int		closest_cell;
	int		i;
	int		hit;

	i = 0;
	hit = 0;
	shortest_dist = INT_MAX;
	closest_cell = tactics->valid_moves->arr[0];
	while (i < (int)tactics->distances->len)
	{
		if (tactics->distances->arr[i] < shortest_dist)
		{
			closest_cell = tactics->valid_moves->arr[i];
			shortest_dist = tactics->distances->arr[i];
			hit = i;
		}
		i++;
	}
	if (DEBUG && shortest_dist < INT_MAX)
		print_debug_choice(hit, shortest_dist, "distance");
	return (closest_cell);
}
