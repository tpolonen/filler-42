/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:16:16 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 19:46:21 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	cell_to_move(int cell)
{
	static t_coord	coord;
	const t_rect	rect = get_piece()->rect;
	t_data			*data;
	char			buf[100];
	char			*ptr;

	data = get_data();
	ft_bzero((void *)buf, 100);
	ptr = buf;
	coord = (t_coord){cell % data->width - rect.x1, cell / data->width - rect.y1};
	ft_memdel((void **)&data->temp);
	ptr = ft_tobase(coord.y, 10, ptr);
	*ptr++ = ' ';
	ptr = ft_tobase(coord.x, 10, ptr);
	data->temp = ft_strdup(buf);
}

static int	can_make_move(t_data *data, int *error, t_strat *strat)
{
	if (ft_getline(0, &(data->temp)) <= 0)
	{
		*error = 9;
		return (0);
	}
	while (ft_strncmp(data->temp, "000", 3) != 0)
	{
		ft_memdel((void **)&data->temp);
		ft_getline(0, &(data->temp));
	}
	ft_bzero(data->oboard_ptr, data->width * data->height);
	ft_bzero(data->xboard_ptr, data->width * data->height);
	ft_bzero(data->xoboard_ptr, data->width * data->height);
	if (!ft_dintarr_clear(&strat->enemy_shape))
		ft_dintarr_create(&strat->enemy_shape, 128, "Enemy shape");
	if (!can_read_board(data, strat->enemy_shape) || \
		!can_read_piece(data, get_piece()))
	{
		*error = 10;
		return (0);
	}
	strategize(data);
	cell_to_move(get_next_move());
	return (1);
}

int	main(void)
{
	t_data	*data;
	int		error;

	data = get_data();
	ft_getline(0, &data->temp);
	error = set_player(data);
	if (error)
		return (clean_exit(data, "Error in player data: ", error));
	error = init_data(data);
	if (error)
		return (clean_exit(data, "Error in map header: ", error));
	while (can_make_move(data, &error, get_strat()))
	{
		if (data->temp)
		{
			ft_putendl(data->temp);
			ft_memdel((void **)&data->temp);
		}
	}
	if (error)
		return (clean_exit(data, "Error in processing turn: ", error));
	return (clean_exit(data, "All done :)", 0));
}
