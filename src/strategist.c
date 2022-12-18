/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:48:51 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 20:00:35 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	should_switch_target(int misses, int turncount)
{
	(void) turncount;
	return ((size_t)misses >= get_strat()->target_shape->len / 2);
}

static void	choose_target(t_strat *strat)
{
	static int	misses;
	int			i;
	int			current_cell;

	if (!strat->target_shape)
	{
		find_new_target(strat);
		return ;
	}
	i = -1;
	while ((size_t)i < strat->target_shape->len)
	{
		current_cell = strat->target_shape->arr[i];
		if (strat->enemy[current_cell] | strat->player[current_cell])
		{
			strat->target_shape->arr[i] = -1;
			misses++;
		}
		i++;
	}
	if (should_switch_target(misses, strat->turncount))
	{
		misses = 0;
		find_new_target(strat);
	}
}

//TODO write some logic to open the game
static void	open_game(t_data *data)
{
	t_strat	*strat;

	(void)data;
	strat = get_strat();
	choose_target(strat);
}

void	strategize(t_data *data)
{
	t_strat		*strat;
	t_dintarr	*enemy_shape;

	strat = get_strat();
	enemy_shape = get_enemy_shape();
	if (enemy_shape->len == 0 && strat->turncount == 0)
		open_game(data);
	else if ((int)enemy_shape->len == strat->enemy_score)
		strat->victory = 1;
	else
		choose_target(strat);
	strat->enemy_score = enemy_shape->len;
}
