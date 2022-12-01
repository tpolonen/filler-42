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

static void	get_juice_scores(t_tactics *tactics,
		t_dintarr *target, t_dintarr *piece_shape)
{
	int			score;
	size_t		valid_idx;
	size_t		target_idx;
	size_t		piece_idx;

	valid_idx = 0;
	while (valid_idx < tactics->valid_moves->len)
	{
		score = 0;
		target_idx = 0;
		while (target_idx < target->len)
		{
			piece_idx = 0;
			while (piece_idx < piece_shape->len)
			{
				score += (target->arr[target_idx] == \
						tactics->valid_moves->arr[valid_idx] + \
						piece_shape->arr[piece_idx]);
				piece_idx++;

			}
			target_idx++;
		}
		ft_dintarr_add(&tactics->juice_scores, score);
	}
}

static int	cell_is_valid_move(t_coord *cell, t_tactics *tactics, t_data *data)
{
	int enemy_cell_hits;
	int player_cell_hits;

	enemy_cell_hits = tactics->enemy_hits->arr[cell->y * \
					  data->width + cell->x];
	player_cell_hits = tactics->player_hits->arr[cell->y * \
					   data->width + cell->x];
	return (enemy_cell_hits == 0 && player_cell_hits == 1);
}

static void	check_validity(t_data *data, t_piece *piece, t_tactics *tactics)
{
	t_coord	cell;

	cell.y = 0;
	while (cell.y < data->height - piece->margin.top - piece->margin.bottom)
	{
		cell.x = 0;
		while (cell.x < data->width && cell.x < data->width - \
				piece->margin.left - piece->margin.right)
		{
			if (cell_is_valid_move(&cell, tactics, data))
				ft_dintarr_add(&tactics->valid_moves, cell.y * data->width + cell.x);
			cell.x++;
		}
		cell.y++;
	}
}

static int	best_move_exists(t_piece *piece, t_coord *center,
		t_coord *nearest, t_coord *best)
{
	t_data		*data;
	t_strat		*strat;
	t_tactics	tactics;

	data = get_data();
	strat = get_strat();
	ft_dintarr_clear(&tactics.enemy_hits);
	count_board_matches(piece, strat->enemy, tactics.enemy_hits);
	ft_dintarr_clear(&tactics.player_hits);
	count_board_matches(piece, strat->player, tactics.player_hits);
	ft_dintarr_clear(&tactics.valid_moves);
	check_validity(data, piece, &tactics);

	return (0);
}

int	valid_move_exists(void)
{
	t_coord	nearest;
	t_coord	best;
	t_coord	center;
	t_strat	*strat;

	find_margins();
	strat = get_strat();
	nearest = (t_coord){0, 0};
	best = (t_coord){0, 0};
	center.x = strat->target->arr[(strat->target->len / 2) % \
			get_data()->width];
	center.y =  strat->target->arr[(strat->target->len / 2) / \
			get_data()->width];
	best_move_exists(get_piece(), &center, &nearest, &best);
	ft_strcpy(get_data()->temp, "0 0");
	return (0);
}
