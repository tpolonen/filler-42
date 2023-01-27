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

	ft_putnbr(coord->x);
	ft_putstr(",");
	ft_putnbr(coord->y);
	ft_putstr(" to cell ");
	cell_to_start = ft_max(0, coord->x) + ft_max(0, coord->y) * data->width;
	ft_putnbr(cell_to_start);
	ft_putstr(" len ");
	check_size = (data->width * piece->height) - ft_min(0, coord->x);
	ft_putnbr(check_size);
	ft_putendl("");
	ret = count(board + cell_to_start, piece->ptr, check_size);
	return (ret);
}

void	count_board_matches(t_piece *piece, char *board, t_dintarr *out)
{
	const t_data	*data = get_data();
	t_coord			coord;	

	coord.y = -piece->margin.top;
	while (coord.y <= data->height - (piece->height - piece->margin.bottom))
	{
		coord.x = -piece->margin.left;
		while (coord.x <= data->width - (piece->width - piece->margin.right))
		{
			ft_dintarr_add(&out, matches_for_coord(&coord, piece, board));
			coord.x++;
		}
		coord.y++;
	}
	ft_putstr("tested matches from ");
	ft_putnbr(-piece->margin.left);
	ft_putstr(",");
	ft_putnbr(-piece->margin.top);
	ft_putstr(" to ");
	ft_putnbr(data->width - (piece->width - piece->margin.right));
	ft_putstr(",");
	ft_putnbr(data->height - (piece->height - piece->margin.bottom));
	ft_putendl("");
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
		if (tactics->juice_scores->arr[i] > 0 && \
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
