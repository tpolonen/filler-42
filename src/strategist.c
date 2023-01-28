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
	static int	last_switch;

	if (turncount > last_switch + 10)
	{
		last_switch = turncount;
		return (1);
	}
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
	while (i < (int)strat->target_shape->len)
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

static void	count_free_space(t_data *data, t_strat *strat)
{
	int	i;

	i = 0;
	strat->free_space = 0;
	while (i < data->width * data->height)
	{
		strat->free_space += data->xoboard_ptr[i] == 0;
		i++;
	}
	/*
	ft_putstr("free space is ");
	ft_putnbr(strat->free_space);
	ft_putendl("");
	*/
}

void	strategize(t_data *data)
{
	t_strat		*strat;
	t_dintarr	*enemy_shape;

	strat = get_strat();
	count_free_space(data, strat);
	enemy_shape = get_enemy_shape();
	if ((int)enemy_shape->len == strat->enemy_score)
		strat->victory = 1;
	else
		choose_target(strat);
	strat->enemy_score = enemy_shape->len;
	strat->turncount++;
}
