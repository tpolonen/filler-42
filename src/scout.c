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

static void	check_board_cell(t_data *data, int pad, t_coord coord,
		t_strat *strat)
{
	if (data->temp[pad + coord.x] == 'o' || data->temp[pad + coord.x] == 'O')
	{
		data->oboard_ptr[coord.y * data->width + coord.x] = 1;
		data->xoboard_ptr[coord.y * data->width + coord.x] = 1;
	}
	if (data->temp[pad + coord.x] == 'x' || data->temp[pad + coord.x] == 'X')
	{
		data->xboard_ptr[coord.y * data->width + coord.x] = 1;
		data->xoboard_ptr[coord.y * data->width + coord.x] = 1;
	}
	if (strat->enemy[coord.x + coord.y * data->width])
		ft_dintarr_add(&strat->enemy_shape, coord.x + coord.y * data->width);
}

int	can_read_board(t_data *data, t_strat *strat)
{
	const int		pad = (int)(ft_strchr(data->temp, ' ') - data->temp) + 1;
	t_coord			coord;

	coord.y = 0;
	while (coord.y < data->height)
	{
		coord.x = 0;
		while (coord.x < data->width)
		{
			check_board_cell(data, pad, coord, strat);
			coord.x++;
		}
		coord.y++;
		ft_memdel((void **)&data->temp);
		ft_getline(0, &(data->temp));
	}
	if (DEBUG)
		ft_putendl_fd("Board read ok", 2);
	return (ft_strncmp(data->temp, "Piece ", 6) == 0);
}

static void	check_piece_row(t_data *data, t_piece *piece, int row)
{
	int	cell_idx;
	int	col;

	ft_memdel((void **)&data->temp);
	ft_getline(0, &(data->temp));
	col = 0;
	while (col < piece->width)
	{
		cell_idx = row * piece->width + col;
		if (data->temp[col] == '*')
		{
			if (col > piece->rect.x2)
				piece->rect.x2 = col;
			if (col < piece->rect.x1)
				piece->rect.x1 = col;
			if (row > piece->rect.y2)
				piece->rect.y2 = row;
			if (row < piece->rect.y1)
				piece->rect.y1 = row;
			ft_dintarr_add(&piece->shape, cell_idx);
		}
		col++;
	}
}

int	can_read_piece(t_data *data, t_piece *piece)
{
	char	*seek;
	int		row;

	seek = data->temp + 6;
	piece->height = (int)ft_strtol(seek, &seek);
	piece->width = (int)ft_strtol(seek, &seek);
	piece->rect = (t_rect){piece->width, piece->height, 0, 0};
	ft_memdel((void **)&(piece->ptr));
	if (!ft_dintarr_clear(&piece->shape))
		ft_dintarr_create(&piece->shape, 32, "Piece");
	row = 0;
	while (row < piece->height)
		check_piece_row(data, piece, row++);
	if ((piece->rect.x2 - piece->rect.x1 <= data->width) && \
			(piece->rect.y2 - piece->rect.y2 <= data->height))
		piece->ptr = make_piece_bitmap(piece, data->width);
	if (DEBUG)
		ft_putendl_fd("Piece read ok", 2);
	return (piece->ptr != NULL);
}

int	set_player(t_data *data)
{
	if (!(data->temp))
		return (2);
	if (ft_strncmp(data->temp, "$$$ exec p", 10) != 0)
		return (3);
	if (ft_strstr(data->temp, "tpolonen.filler") == NULL)
		return (4);
	data->player = 'x';
	if (ft_strstr(data->temp, "p1") != NULL)
		data->player = 'o';
	return (data->player == 0);
}
