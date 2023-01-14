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

static void	close_dintarrs(t_dintarr *enemy_shape, t_tactics *tactics,
		t_strat *strat)
{
	if (enemy_shape)
		ft_memdel((void **)&enemy_shape->arr);
	if (strat->target_shape)
		ft_dintarr_close(&strat->target_shape, NULL);
	if (tactics->source)
		ft_dintarr_close(&tactics->source, NULL);
	if (tactics->valid_moves)
		ft_dintarr_close(&tactics->valid_moves, NULL);
	if (tactics->enemy_hits)
		ft_dintarr_close(&tactics->enemy_hits, NULL);
	if (tactics->player_hits)
		ft_dintarr_close(&tactics->player_hits, NULL);
	if (tactics->juice_scores)
		ft_dintarr_close(&tactics->juice_scores, NULL);
	if (tactics->distances)
		ft_dintarr_close(&tactics->distances, NULL);
}

int	clean_exit(t_data *data, const char *str, int error)
{
	ft_memdel((void **)&data->xboard_ptr);
	ft_memdel((void **)&data->oboard_ptr);
	ft_memdel((void **)&data->xoboard_ptr);
	ft_memdel((void **)&data->temp);
	ft_memdel((void **)&get_piece()->ptr);
	ft_memdel((void **)&get_strat()->target_ptr);
	ft_memdel((void **)&get_strat()->values_ptr);
	close_dintarrs(get_enemy_shape(), get_tactics(), get_strat());
	if (str)
		ft_putstr(str);
	if (error)
		ft_putnbr(error);
	ft_putendl("");
	return (error);
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
		i++;
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
		clean_exit(get_data(), "Allocation failed ", -1);
	ft_bzero(alloc, size);
	return (alloc);
}
