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

static int	set_player(t_data *data)
{
	if (!(data->temp))
		return (2);
	if (ft_strncmp(data->temp, "$$$ exec p", 10) != 0)
		return (3);
	if (ft_strstr(data->temp, "tpolonen.filler") == NULL)
		return (4);
	if (ft_strstr(data->temp, "p1") != NULL)
		data->player = 'o';
	else
		data->player = 'x';
	return (data->player == 0);
}

static int	init_data(t_data *data)
{
	char	*seek;

	if (!(data->temp))
		return (2);
	if (ft_strncmp(data->temp, "Plateau ", 8) != 0)
		return (5);
	if (ft_strchr(data->temp, ':') == NULL)
		return (6);
	seek = data->temp + 8;
	data->height = (int)ft_strtol(seek, &seek);
	data->width = (int)ft_strtol(seek, &seek);
	data->oboard_ptr = (char *)xalloc(data->width * data->height);
	data->xboard_ptr = (char *)xalloc(data->width * data->height);
	if (data->oboard_ptr == NULL || data->xboard_ptr == NULL)
		return (7);
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
	return ((data->width <= 0) || (data->height <= 0));
}

static int	get_turn(t_data *data, int *error)
{
	if (ft_getline(0, &(data->temp)) <= 0)
	{
		data->temp = NULL;
		return (0);
	}
	while (ft_strncmp(data->temp, "000", 3) != 0)
	{
		ft_memdel((void **)&data->temp);
		ft_getline(0, &(data->temp));
	}
	*error = read_board(data);
	if (*error)
		return (0);
	*error = read_piece(data);
	if (*error)
		return (0);
	return (plan_move(data));
}

static int	clean_exit(t_data *data, const char *str, int error)
{
	if (data->oboard_ptr)
		ft_memdel((void **)&data->oboard_ptr);
	if (data->xboard_ptr)
		ft_memdel((void **)&data->xboard_ptr);
	if (data->temp)
		ft_memdel((void **)&data->temp);
	if (get_piece()->ptr)
		ft_memdel((void **)&get_piece()->ptr);
	if (str)
		ft_putstr(str);
	if (error)
		ft_putnbr(error);
	ft_putendl("");
	return (error);
}

int	main(void)
{
	static t_data	*data;
	int				error;

	data = get_data();
	ft_getline(0, &data->temp);
	error = set_player(data);
	if (error)
		return (clean_exit(data, "Error in player data: ", error));
	ft_memdel((void **)&data->temp);
	ft_getline(0, &(data->temp));
	error = init_data(data);
	if (error)
		return (clean_exit(data, "Error in map header: ", error));
	ft_memdel((void **)&data->temp);
	while (get_turn(data, &error))
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
