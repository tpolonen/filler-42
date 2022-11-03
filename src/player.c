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

static int open_game(t_data *data)
{
	(void)data;
	return (1);
}

static int should_switch_target(int misses, int turncount)
{
	(void) turncount;
	return ((size_t)misses >= get_strat()->target_count / 2);
}

static int make_move(t_data *data, t_strat *strat)
{
	static int	misses;
	int			i;
	int			error;
	//do we already have an advance targeted? continue the offense
	//otherwise get new target
	//if error, get_target sets strat->target_count to arbitrary negative number
	//and returns !0
	error = 0;
	if (!strat->target)
		error = get_target(data, strat);
	i = 0;
	while ((size_t)i < strat->target_count)
	{
		if (strat->enemy[strat->target[i]] | strat->player[strat->target[i]])
		{
			strat->target[i] = -1;
			misses++;
		}
		i++;
	}
	if (should_switch_target(misses, data->turncount))
	{
		misses = 0;
		error = get_target(data, strat);
	}
	if (error)
		return (error);
	return (0);
	//when we have a target, find the closest own block to it with floodfill
	//start blindly placing the piece starting from that position
	//get like three first locations or something
	//choose the one that blocks most of the targeted area (test with floodfill)
	//if there's no such pos? choose the place that's the nearest to target
	//maybe take the average of target or something
}

int	plan_move(t_data *data)
{
	t_strat	*strat;
	int		cur_enemy_score;

	ft_memdel((void **)&data->temp);
	strat = get_strat();
	if (!strat->victory)
	{
		cur_enemy_score = count(strat->enemy, data->width * data->height);
		if (cur_enemy_score == 0 && data->turncount == 0)
			open_game(data);
		else if (cur_enemy_score == strat->enemy_score)
			strat->victory = 1;
		strat->enemy_score = cur_enemy_score;
		if (make_move(data, strat))
			return (0);
	}
	else
		data->temp = ft_strdup("0 0\n");
	data->turncount++;
	ft_memdel((void **)&get_piece()->ptr);
	return (1);
}
