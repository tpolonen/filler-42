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

static int	get_values(char *board, t_dintarr *shape, int *values)
{
	return (0);
}

static int	get_target(t_data *data, t_strat *strat)
{
	t_dintarr	*shape;
	t_dintarr	*target;
	int			*values;
	int			i;

	if (strat->target)
		ft_memdel((void **)strat->target);
	i = 0;
	while (i < data->width * data->height && data->enemy[i] == 0)
		i++;
	shape = floodfill(data->enemy, i, SIZE_MAX, 0); 
	if (!shape)
	{
		strat->target_count = INT_MIN;
		return (1);
	}
	values = (int *)xalloc(sizeof(int) * shape->len;
}

static int make_move(t_data *data, t_piece *piece, t_strat *strat)
{
	static int	misses;
	int			i;
	int			error;
	//do we already have an advance targeted? continue the offense
	//otherwise get new target
	//if error, get_target sets strat->target_count to arbitrary negative number
	//and returns !0
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
	if ((size_t)misses >= strat->target_count / 2)
	{
		misses = 0;
		error = get_target(data, strat);
	}
	if (error)
	{
		ft_memdel((void **)&piece->ptr);
		return (error);
	}
	//when we have a target, find the closest own block to it with floodfill
	//start blindly placing the piece starting from that position
	//get like three first locations or something
	//choose the one that blocks most of the targeted area (test with floodfill)
	//if there's no such pos? choose the place that's the nearest to target
	//maybe take the average of target or something
}

int	plan_move(t_data *data, t_piece *piece)
{
	t_strat	*strat;
	int		cur_enemy_score;

	ft_memdel((void **)&data->temp);
	strat = get_strat();
	if (!strat->victory)
	{
		cur_enemy_score = count(strat->enemy, data->width * data->height);
		if (cur_enemy_score == 0)
			start_game(data, piece);
		else if (cur_enemy_score == strat->enemy_score)
			strat->victory = 1;
		strat->enemy_score = cur_enemy_score;
		if (make_move(data, piece, strat))
			return (0);
	}
	else
		data->temp = ft_strdup("0 0\n");
	ft_memdel((void **)&piece->ptr);
	return (1);
}
