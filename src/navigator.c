/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:43:16 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 17:52:40 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	get_offset(t_data *data)
{
	int	ret;

	ret = 0;
	while (*data->temp == '0')
		ret++;
	return (ret);
}

int	can_read_board(t_data *data)
{
	int		row;
	int		x;
	int		offset;

	row = 0;
	offset = get_offset(data);
	ft_bzero(data->oboard_ptr, data->width * data->height);
	ft_bzero(data->xboard_ptr, data->width * data->height);
	while (row < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			if (data->temp[offset + x] == 'o' || data->temp[offset + x] == 'O')
				*(data->oboard_ptr + (row * data->width) + x) = 1;
			if (data->temp[offset + x] == 'x' || data->temp[offset + x] == 'X')
				*(data->xboard_ptr + (row * data->width) + x) = 1;
		}
		ft_memdel((void **)&data->temp);
		ft_getline(0, &(data->temp));
		row++;
	}
	if (ft_strncmp(data->temp, "Piece ", 6) != 0)
		return (0);
	return (1);
}

int	can_read_piece(t_data *data, t_piece *piece)
{
	char	*seek;
	int		row;
	int		x;

	seek = data->temp + 6;
	piece->height = (int)ft_strtol(seek, &seek);
	piece->width = (int)ft_strtol(seek, &seek);
	piece->ptr = (char *)xalloc(data->width * piece->height);
	if (piece->ptr == NULL)
		return (0);
	row = 0;
	while (row < piece->height)
	{
		ft_memdel((void **)&data->temp);
		ft_getline(0, &(data->temp));
		x = -1;
		while (++x < piece->width)
			if (data->temp[x] == '*')
				*(piece->ptr + (row * data->width) + x) = 1;
		row++;
	}
	return (0);
}

int	set_player(t_data *data)
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

int	init_data(t_data *data)
{
	char	*seek;

	if (!(data->temp))
		return (2);
	if ((ft_strncmp(data->temp, "Plateau ", 8) != 0) || \
			(ft_strchr(data->temp, ':') == NULL))
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
