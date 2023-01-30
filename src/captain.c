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

static void	get_juice_scores(t_tactics *tactics)
{
	const t_strat	*strat = get_strat();
	const t_piece	*piece = get_piece();
	const t_data	*data = get_data();
	int				score;
	size_t			valid_idx;

	if (!ft_dintarr_clear(&tactics->juice_scores))
		ft_dintarr_create(&tactics->juice_scores, data->width * data->height, \
				"Juice scores :)");
	valid_idx = 0;
	while (valid_idx < tactics->valid_moves->len)
	{
		score = count(strat->target_ptr + tactics->valid_moves->arr[valid_idx],
				piece->ptr, data->width * piece->height);
		ft_dintarr_add(&tactics->juice_scores, score);
		valid_idx++;
	}
}

static void	get_dist_scores(t_tactics *tactics, t_strat *strat)
{
	int				dist;
	size_t			valid_idx;
	t_coord			current;
	const int		board_width = get_data()->width;
	const t_coord	center = cell_to_coord(\
			strat->target_shape->arr[0], board_width);

	if (!ft_dintarr_clear(&tactics->distances))
		ft_dintarr_create(&tactics->distances, board_width * \
				get_data()->height, "Dist scores :(");
	valid_idx = 0;
	while (valid_idx < tactics->valid_moves->len)
	{
		current = cell_to_coord(tactics->valid_moves->arr[valid_idx], \
				board_width);
		dist = ft_abs(center.x - current.x) + \
				ft_abs(center.y - current.y);
		ft_dintarr_add(&tactics->distances, dist);
		valid_idx++;
	}
}

static void	check_validity(t_data *data, t_piece *piece, t_tactics *tactics)
{
	t_coord	cell;
	int		enemy_cell_hits;
	int		player_cell_hits;

	cell.y = 0;
	while (cell.y < data->height - (piece->rect.y2 - piece->rect.y1))
	{
		cell.x = 0;
		while (cell.x < data->width - (piece->rect.x2 - piece->rect.x1))
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

static int	best_move_exists(t_piece *piece, int *nearest, int *best)
{
	t_strat		*strat;
	t_tactics	*tactics;

	strat = get_strat();
	tactics = get_tactics();
	if (!ft_dintarr_clear(&tactics->enemy_hits))
		ft_dintarr_create(&tactics->enemy_hits, 256, "Enemy hits");
	count_board_matches(piece, strat->enemy, tactics->enemy_hits);
	if (!ft_dintarr_clear(&tactics->player_hits))
		ft_dintarr_create(&tactics->player_hits, 256, "Player hits");
	count_board_matches(piece, strat->player, tactics->player_hits);
	if (!ft_dintarr_clear(&tactics->valid_moves))
		ft_dintarr_create(&tactics->valid_moves, 64, "Valid moves");
	check_validity(get_data(), piece, tactics);
	get_juice_scores(tactics);
	*best = find_juiciest_cell(tactics);
	if (*best < 0)
	{
		get_dist_scores(tactics, strat);
		*nearest = find_closest_cell(tactics);
		return (0);
	}
	return (1);
}

int	get_next_move(void)
{
	int		nearest;
	int		best;

	nearest = 0;
	best = -1;
	if (get_strat()->victory > 1)
		return (0);
	if (best_move_exists(get_piece(), &nearest, &best))
		return (best);
	else
		return (nearest);
}
