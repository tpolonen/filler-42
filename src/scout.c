/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:43:16 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 17:52:40 by tpolonen         ###   ########.fr       */
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

int	can_read_board(t_data *data, t_dintarr *enemy_shape)
{
	const t_strat	*strat = get_strat();
	const int		pad = (int)(ft_strchr(data->temp, ' ') - data->temp) + 1;
	int				row;
	int				x;

	row = -1;
	while (++row < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			if (data->temp[pad + x] == 'o' || data->temp[pad + x] == 'O')
				data->oboard_ptr[row * data->width + x] = 1;
			if (data->temp[pad + x] == 'x' || data->temp[pad + x] == 'X')
				data->xboard_ptr[row * data->width + x] = 1;
			if (strat->enemy[x + row * data->width])
				ft_dintarr_add(&enemy_shape, x + row * data->width);
			data->xoboard_ptr[row * data->width + x] = \
				data->oboard_ptr[row * data->width + x] || 
				data->xboard_ptr[row * data->width + x];
		}
		ft_memdel((void **)&data->temp);
		ft_getline(0, &(data->temp));
	}
	return (ft_strncmp(data->temp, "Piece ", 6) == 0);
}

static void	check_cell(t_piece *piece, int row, int col)
{
	const t_data	*data = get_data();

	if (data->temp[col] == '*')
	{
		piece->ptr[row * data->width + col] = 1;
		ft_dintarr_add(&piece->shape,
			piece->ptr[row * data->width + col]);
	}
}

int	can_read_piece(t_data *data, t_piece *piece)
{
	char	*seek;
	int		row;
	int		col;

	seek = data->temp + 6;
	piece->height = (int)ft_strtol(seek, &seek);
	piece->width = (int)ft_strtol(seek, &seek);
	piece->ptr = (char *)xalloc(data->width * piece->height);
	if (!ft_dintarr_clear(&piece->shape))
		ft_dintarr_create(&piece->shape, 8);
	row = 0;
	while (row < piece->height && piece->ptr)
	{
		ft_memdel((void **)&data->temp);
		ft_getline(0, &(data->temp));
		col = 0;
		while (col < piece->width)
			check_cell(piece, row, col++);
		row++;
	}
	return (piece->ptr != NULL);
}

int	set_player(t_data *data)
{
	t_strat	*strat;

	strat = get_strat();
	if (!(data->temp))
		return (2);
	if (ft_strncmp(data->temp, "$$$ exec p", 10) != 0)
		return (3);
	if (ft_strstr(data->temp, "tpolonen.filler") == NULL)
		return (4);
	strat->player = data->oboard_ptr;
	strat->enemy = data->oboard_ptr;
	if (ft_strstr(data->temp, "p1") != NULL)
	{
		strat->enemy = data->xboard_ptr;
		data->player = 'o';
	}
	else
	{
		strat->player = data->xboard_ptr;
		data->player = 'x';
	}
	return (data->player == 0);
}
