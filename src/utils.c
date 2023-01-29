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

static void	close_dintarrs(t_tactics *tactics,
		t_strat *strat)
{
	if (strat->enemy_shape)
		ft_dintarr_close(&strat->enemy_shape, NULL);
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
	ft_memdel((void **)&get_strat()->values_arr);
	close_dintarrs(get_tactics(), get_strat());
	if (str)
		ft_putstr(str);
	if (error)
		ft_putnbr(error);
	ft_putendl("");
	return (error);
}

t_coord	cell_to_coord(int cell, int board_width)
{
	return ((t_coord){cell % board_width, cell / board_width});
}

char	*make_piece_bitmap(t_piece *piece, int board_width)
{
	char	*ptr;
	int		shape_idx;
	int		cell_idx;
	t_coord	coord;

	ptr = (char *)xalloc(piece->height * board_width);
	shape_idx = 0;
	while (ptr && shape_idx < (int)piece->shape->len)
	{
		cell_idx = piece->shape->arr[shape_idx];
		coord = (t_coord){(cell_idx % piece->width) - piece->rect.x1, \
			(cell_idx / piece->width) - piece->rect.y1};
		cell_idx = coord.x + coord.y * board_width;
		ptr[cell_idx] = 1;
		piece->shape->arr[shape_idx] = cell_idx;
		shape_idx++;
	}
	return (ptr);
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
