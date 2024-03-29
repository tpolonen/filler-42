/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:16:16 by tpolonen          #+#    #+#             */
/*   Updated: 2023/01/31 19:07:00 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	init_data(t_data *data)
{
	char		*seek;
	t_strat		*strat;

	ft_getline(0, &(data->temp));
	if ((ft_strncmp(data->temp, "Plateau ", 8)) || \
			(ft_strchr(data->temp, ':') == NULL))
		return (6);
	seek = data->temp + 8;
	data->height = (int)ft_strtol(seek, &seek);
	data->width = (int)ft_strtol(seek, &seek);
	data->oboard_ptr = (char *)xalloc(data->width * data->height);
	data->xboard_ptr = (char *)xalloc(data->width * data->height);
	data->xoboard_ptr = (char *)xalloc(data->width * data->height);
	strat = get_strat();
	strat->target_ptr = (char *)xalloc(data->width * data->height);
	strat->player = data->oboard_ptr;
	strat->enemy = data->oboard_ptr;
	if (data->player == 'x')
		strat->player = data->xboard_ptr;
	else
		strat->enemy = data->xboard_ptr;
	ft_memdel((void **)&data->temp);
	return ((data->width <= 0) || (data->height <= 0));
}

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
	coord = (t_coord){cell % data->width - rect.x1, \
		cell / data->width - rect.y1};
	ft_memdel((void **)&data->temp);
	ptr = ft_tobase(coord.y, 10, ptr);
	*ptr++ = ' ';
	ptr = ft_tobase(coord.x, 10, ptr);
	data->temp = ft_strdup(buf);
	if (DEBUG)
	{
		ft_putstr_fd("Chose this move: [", 2);
		ft_putstr_fd(buf, 2);
		ft_putendl_fd("]\n", 2);
	}
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
	if (!can_read_board(data, strat) || \
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
	ft_memdel((void **)&data->temp);
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
