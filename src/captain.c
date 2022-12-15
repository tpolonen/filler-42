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

/* I think this might be shit?
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
*/

static void	get_juice_scores(t_tactics *tactics)
{
	const t_strat	*strat = get_strat();
	const t_piece	*piece = get_piece();
	int				score;
	size_t			valid_idx;

	valid_idx = 0;
	while (valid_idx < tactics->valid_moves->len)
	{
		score = count(strat->target_ptr + tactics->valid_moves->arr[valid_idx],
				piece->ptr, piece->width * piece->height);
		ft_dintarr_add(&tactics->juice_scores, score);
		valid_idx++;
	}
	ft_memdel((void **)&strat->target_ptr);
}

static void	get_dist_scores(t_tactics *tactics,
		t_dintarr *target, t_coord *origin)
{
	int		dist;
	size_t	valid_idx;
	t_coord	target_coord;
	int		mid_target;
	int		board_width;

	valid_idx = 0;
	mid_target = target->arr[target->len / 2];
	board_width = get_data()->width;
	target_coord = (t_coord){target->arr[mid_target] % board_width,
		target->arr[mid_target] / board_width};
	while (valid_idx < tactics->valid_moves->len)
	{
		dist = ft_abs(target_coord.x - origin->x) + \
				ft_abs(target_coord.y - origin->y);
		ft_dintarr_add(&tactics->distances, dist);
	}
}

static void	check_validity(t_data *data, t_piece *piece, t_tactics *tactics)
{
	t_coord	cell;
	int		enemy_cell_hits;
	int		player_cell_hits;

	cell.y = 0;
	while (cell.y < data->height - piece->margin.top - piece->margin.bottom)
	{
		cell.x = 0;
		while (cell.x < data->width && cell.x < data->width - \
				piece->margin.left - piece->margin.right)
		{
			enemy_cell_hits = tactics->enemy_hits->arr[cell.y * \
						data->width + cell.x];
			player_cell_hits = tactics->player_hits->arr[cell.y * \
						data->width + cell.x];
			if (enemy_cell_hits == 0 && player_cell_hits == 1)
				ft_dintarr_add(&tactics->valid_moves,
					cell.y * data->width + cell.x);
			cell.x++;
		}
		cell.y++;
	}
}

static int	best_move_exists(t_piece *piece, t_coord *center,
		int *nearest, int *best)
{
	t_strat		*strat;
	t_tactics	*tactics;

	strat = get_strat();
	tactics = get_tactics();
	ft_dintarr_clear(&tactics->enemy_hits);
	count_board_matches(piece, strat->enemy, tactics->enemy_hits);
	ft_dintarr_clear(&tactics->player_hits);
	count_board_matches(piece, strat->player, tactics->player_hits);
	ft_dintarr_clear(&tactics->valid_moves);
	check_validity(get_data(), piece, tactics);
	get_juice_scores(tactics);
	*best = find_juiciest_cell(tactics);
	if (*best < 0)
	{
		get_dist_scores(tactics, strat->target_shape, center);
		*nearest = find_closest_cell(tactics);
		return (0);
	}
	return (1);
}

int	get_next_move(void)
{
	int		nearest;
	int		best;
	t_coord	center;
	t_strat	*strat;

	find_margins();
	strat = get_strat();
	nearest = 0;
	best = -1;
	center = (t_coord){0, 0};
	center.x = strat->target_shape->arr[(strat->target_shape->len / 2) % \
			get_data()->width];
	center.y = strat->target_shape->arr[(strat->target_shape->len / 2) / \
			get_data()->width];
	if (best_move_exists(get_piece(), &center, &nearest, &best))
		return (best);
	else
		return (nearest);
}
