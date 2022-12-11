/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:29:40 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 17:38:41 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	close_dintarrs(void)
{
	t_dintarr	*enemy_shape;
	t_dintarr	*target;
	t_dintarr	*valid_moves;
	t_dintarr	*enemy_hits;
	t_dintarr	*player_hits;
	t_dintarr	*juice_scores;
	t_dintarr	*distance_scores;

	enemy_shape = get_enemy_shape();
	valid_moves = get_tactics()->valid_moves;
	target = get_strat()->target;
	enemy_hits = get_tactics()->enemy_hits;
	player_hits = get_tactics()->player_hits;
	juice_scores = get_tactics()->juice_scores;
	distance_scores = get_tactics()->distance_scores;
	ft_dintarr_close(&valid_moves, NULL);
	ft_dintarr_close(&enemy_shape, NULL);
	ft_dintarr_close(&target, NULL);
	ft_dintarr_close(&enemy_hits, NULL);
	ft_dintarr_close(&player_hits, NULL);
	ft_dintarr_close(&juice_scores, NULL);
	ft_dintarr_close(&distance_scores, NULL);
}

int	clean_exit(t_data *data, const char *str, int error)
{
	ft_memdel((void **)&data->xboard_ptr);
	ft_memdel((void **)&data->oboard_ptr);
	ft_memdel((void **)&data->xoboard_ptr);
	ft_memdel((void **)&data->temp);
	ft_memdel((void **)&get_piece()->ptr);
	close_dintarrs();
	if (str)
		ft_putstr(str);
	if (error)
		ft_putnbr(error);
	ft_putendl("");
	return (error);
}

int	is_cell_filled(int cell)
{
	const t_strat	*strat = get_strat();

	return (strat->enemy[cell] | strat->player[cell]);
}

void	find_margins(void)
{
	t_piece			*piece;
	t_dintarr		*shape;
	size_t			i;

	piece = get_piece();
	shape = piece->shape;
	piece->margin.top = shape->arr[0] / piece->width;
	piece->margin.bottom = shape->arr[piece->shape->len - 1] / piece->width;
	piece->margin.left = piece->width - 1;
	piece->margin.right = 0;
	i = 0;
	while (i < shape->len)
	{
		if (shape->arr[i] % piece->width < piece->margin.left)
			piece->margin.left = shape->arr[i] / piece->width;
		if (shape->arr[i] % piece->width < piece->margin.right)
			piece->margin.right = piece->width - shape->arr[i] % piece->width;
	}
}

void	*xalloc(size_t min_size)
{
	size_t	size;
	void	*alloc;

	size = 2;
	while (size < min_size)
		size *= 2;
	alloc = malloc(size);
	if (!alloc)
		clean_exit(get_data(), "Allocation failed", 0);
	ft_bzero(alloc, size);
	return (alloc);
}
