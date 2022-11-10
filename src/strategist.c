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

static void	open_game(t_data *data)
{
	(void)data;
}

static int	should_switch_target(int misses, int turncount)
{
	(void) turncount;
	return ((size_t)misses >= get_strat()->target->len / 2);
}

static void	choose_target(t_data *data, t_strat *strat)
{
	static int	misses;
	int			i;

	if (!strat->target)
		find_new_target(strat);
	i = 0;
	while ((size_t)i < strat->target->len)
	{
		if (strat->enemy[strat->target->arr[i]] || \
				strat->player[strat->target->arr[i]])
		{
			strat->target->arr[i] = -1;
			misses++;
		}
		i++;
	}
	if (should_switch_target(misses, data->turncount))
	{
		misses = 0;
		find_new_target(strat);
	}
}

void	strategize(t_data *data)
{
	t_strat		*strat;
	t_dintarr	*enemy_shape;

	strat = get_strat();
	enemy_shape = get_enemy_shape();
	if (enemy_shape->len == 0 && data->turncount == 0)
		open_game(data);
	else if ((int)enemy_shape->len == strat->enemy_score)
		strat->victory = 1;
	else
		choose_target(data, strat);
	strat->enemy_score = enemy_shape->len;
}
