/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captain.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 17:48:51 by tpolonen          #+#    #+#             */
/*   Updated: 2022/11/10 19:45:45 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	*count_board_matches(char* board, int target)
{
	int			*ret;
	int 		i;
	const int	size = get_data()->width * get_data()->height;

	ret = (int *)xalloc(size);
	i = 0;
	while (i < size)
	{
		ret[i] = count()
	}
	return (ret);
}

static int	best_move_exists(t_piece *piece, t_coord *center,
		t_coord *nearest, t_coord *best)
{
	int	col;
	int	row;
	int	*enemy_hits;
	int	*player_hits;

	return (0);
}

void	align_piece(void)
{

}

int	valid_move_exists(void)
{
	t_coord	nearest;
	t_coord	best;
	t_coord	center;

	find_margins();
	align_piece();
	nearest = (t_coord){0, 0};
	best = (t_coord){0, 0};
	center.x = get_strat()->target->arr[(get_strat()->target->len / 2) % \
			get_data()->width];
	center.y =  get_strat()->target->arr[(get_strat()->target->len / 2) / \
			get_data()->width];
	best_move_exists(get_piece(), &center, &nearest, &best);
	ft_strcpy(get_data()->temp, "0 0");
	return (0);
}
