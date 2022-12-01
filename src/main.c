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

static void	align_piece(void)
{
	const t_data	*data = get_data();
	t_piece			*piece;
	char			*map;
	int				i;

	piece = get_piece();
	map = piece->ptr;
	i = 0;
	while (i < data->width * data->height)
	{
		map[i] <<= piece->margin.left;
		map[i] <<= piece->margin.top * data->width;
		i++;
	}
}

int	init_data(t_data *data)
{
	char	*seek;

	ft_getline(0, &(data->temp));
	if ((ft_strncmp(data->temp, "Plateau ", 8)) || \
			(ft_strchr(data->temp, ':') == NULL))
		return (6);
	seek = data->temp + 8;
	data->height = (int)ft_strtol(seek, &seek);
	data->width = (int)ft_strtol(seek, &seek);
	data->oboard_ptr = (char *)xalloc(data->width * data->height * 3);
	if (data->player == 'x')
	{
		get_strat()->player = data->xboard_ptr;
		get_strat()->enemy = data->oboard_ptr;
	}
	else
	{
		get_strat()->player = data->oboard_ptr;
		get_strat()->enemy = data->xboard_ptr;
	}
	ft_memdel((void **)&data->temp);
	return ((data->width <= 0) || (data->height <= 0));
}

static int	can_make_move(t_data *data, int *error, t_dintarr *enemy_shape)
{
	if (ft_getline(0, &(data->temp)) <= 0)
	{
		data->temp = NULL;
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
	ft_dintarr_clear(&enemy_shape);
	if (!can_read_board(data, enemy_shape) ||
			!can_read_piece(data, get_piece()))
	{
		*error = 10;
		return (0);
	}
	align_piece();
	strategize(data);
	return (valid_move_exists());
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
	while (can_make_move(data, &error, get_enemy_shape()))
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
