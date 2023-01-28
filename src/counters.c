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
	int	ret;

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

static int	matches_for_coord(t_coord *coord, t_piece *piece, char *board)
{
	const t_data	*data = get_data();
	int				cell_to_start;
	int				check_size;
	int				ret;

	/*
	ft_putnbr(coord->x);
	ft_putstr(",");
	ft_putnbr(coord->y);
	ft_putstr(" to cell ");
	*/
	cell_to_start = coord->x + (coord->y * data->width);
	/*
	ft_putnbr(cell_to_start);
	ft_putstr(" len ");
	*/
	check_size = data->width * (piece->rect.y2 - piece->rect.y1 + 1);
	/*
	ft_putnbr(check_size);
	ft_putendl("");
	*/
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
	/*
	for (int i = 0; i < (int)out->len; i++)
	{
		if (i % data->width == 0)
			ft_putchar('\n');
		ft_putchar('0' + (out->arr[i] % 10));
	}
	ft_putchar('\n');
*/
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
	if (best_cell > 0)
	{
		dprintf(2, "juiciest cell found, was valid_idx %c cell %d with score of %d\n\n", 'A' + hit, best_cell, hiscore);
	}
	return (best_cell);
}

int	find_closest_cell(t_tactics *tactics)
{
	int		shortest_dist;
	int		closest_cell;
	int		i;
	int		hit;

	i = 0;
	shortest_dist = INT_MAX;
	closest_cell = tactics->valid_moves->arr[tactics->valid_moves->len - 1];
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
	dprintf(2, "no juicy cell, closest one is valid_idx %c cell %d with dist of %d\n\n", 'A' + hit, closest_cell, shortest_dist);
	return (closest_cell);
}
