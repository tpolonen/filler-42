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

static int	should_switch_target(int misses, int turncount)
{
	static int	last_switch;

	return (1);
	if (turncount > last_switch + 10 || \
			misses >= (int)get_strat()->target_shape->len / 2)
	{
		ft_putstr_fd("switched target\n", 2);
		last_switch = turncount;
		return (1);
	}
	return (0);
}

static void	choose_target(t_strat *strat)
{
	static int	misses;
	int			i;
	int			current_cell;


	//ft_putstr_fd("do we choose target???\n", 2);
	/*
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(" strat->enemy:", 2);
	ft_putnbr_fd((int)(size_t)strat->enemy, 2);
	ft_putstr_fd(" strat->player:", 2);
	ft_putnbr_fd((int)(size_t)strat->player, 2);
	ft_putstr_fd("\n", 2);
	*/
	if (!strat->target_shape)
	{
		//ft_putstr_fd("no target_shape in choose_target\n", 2);
		find_new_target(strat);
		return ;
	}
	i = 0;
	/*
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("strat->target_shape->len:", 2);
	ft_putnbr_fd((int)strat->target_shape->len, 2);
	ft_putstr_fd("\n", 2);
	*/
	while (i < (int)strat->target_shape->len)
	{
		current_cell = strat->target_shape->arr[i];
		/*
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("current_cell:", 2);
		ft_putnbr_fd(current_cell, 2);
		ft_putstr_fd("\n", 2);
		*/
		if (strat->enemy[current_cell] || strat->player[current_cell])
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

	//ft_putstr_fd("do we strategize???\n", 2);
	strat = get_strat();
	count_free_space(data, strat);
	enemy_shape = strat->enemy_shape;
	/*
	ft_putstr_fd("STRATEG enemy_shape->alloced:", 2);
	ft_putnbr_fd((int)enemy_shape->alloced, 2);
	ft_putstr_fd(" len:", 2);
	ft_putnbr_fd((int)enemy_shape->len, 2);
	ft_putstr_fd("\n", 2);
	*/
	if (enemy_shape->len > 0 && (int)enemy_shape->len == strat->enemy_score)
		strat->victory += 1;
	if (strat->victory < 2)
	{
		//ft_putstr_fd("no victory, choosing new target\n", 2);
		choose_target(strat);
	}
	strat->enemy_score = enemy_shape->len;
	strat->turncount++;
}
