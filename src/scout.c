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

static int	get_offset(t_data *data)
{
	int	ret;

	ret = 0;
	while (*(data->temp + ret) != ' ')
		ret++;
	return (++ret);
}

int	can_read_board(t_data *data, t_dintarr *enemy_shape)
{
	int			row;
	int			x;
	const int	offset = get_offset(data);

	row = -1;
	while (++row < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			if (data->temp[offset + x] == 'o' || data->temp[offset + x] == 'O')
			{
				ft_dintarr_add(&enemy_shape, row * data->width + x);
				data->oboard_ptr[row * data->width + x] = 1;
				data->xoboard_ptr[row * data->width + x] = 1;
			}
			if (data->temp[offset + x] == 'x' || data->temp[offset + x] == 'X')
				data->xboard_ptr[row * data->width + x] = 1;
			data->xoboard_ptr[row * data->width + x] =
					data->xoboard_ptr[row * data->width + x] == 1;
		}
		ft_memdel((void **)&data->temp);
		ft_getline(0, &(data->temp));
	}
	return (ft_strncmp(data->temp, "Piece ", 6) == 0);
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
	ft_dintarr_clear(&piece->shape);
	row = 0;
	while (row < piece->height && piece->ptr)
	{
		ft_memdel((void **)&data->temp);
		ft_getline(0, &(data->temp));
		x = -1;
		while (++x < piece->width)
			if (data->temp[x] == '*')
			{
				piece->ptr[row * data->width + x] = 1;
				ft_dintarr_add(&piece->shape,
						piece->ptr[row * data->width + x]);
			}
		row++;
	}
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
	if (ft_strstr(data->temp, "p1") != NULL)
		data->player = 'o';
	else
		data->player = 'x';
	return (data->player == 0);
}


