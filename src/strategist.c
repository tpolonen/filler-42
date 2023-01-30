/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:48:51 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 20:00:35 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

static int	should_switch_target(int turncount)
{
	return (turncount);
}

static void	choose_target(t_strat *strat)
{
	if (!strat->target_shape)
	{
		find_new_target(strat);
		return ;
	}
	if (should_switch_target(strat->turncount))
		find_new_target(strat);
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
}

void	strategize(t_data *data)
{
	t_strat		*strat;
	t_dintarr	*enemy_shape;

	strat = get_strat();
	count_free_space(data, strat);
	enemy_shape = strat->enemy_shape;
	if (enemy_shape->len > 0 && (int)enemy_shape->len == strat->enemy_score)
		strat->victory += 1;
	if (strat->victory < 2)
		choose_target(strat);
	strat->enemy_score = enemy_shape->len;
	strat->turncount++;
}
