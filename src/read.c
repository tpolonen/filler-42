/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:43:16 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/06 17:12:17 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int const g_len = 4;

int	read_board(t_data *data)
{
	int		row;
	int		x;

	row = 0;
	ft_bzero(data->oboard_ptr, data->width * data->height);
	ft_bzero(data->xboard_ptr, data->width * data->height);
	while (row < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (data->temp[g_len + x] == 'o' || data->temp[g_len + x] == 'O')
				*(data->oboard_ptr + (row * data->width) + x) = 1;
			if (data->temp[g_len + x] == 'x' || data->temp[g_len + x] == 'X')
				*(data->xboard_ptr + (row * data->width) + x) = 1;
			x++;
		}
		free(data->temp);
		ft_getline(0, &(data->temp));
		row++;
	}
	if (ft_strncmp(data->temp, "Piece ", 6) != 0)
		return (8);
	return (0);
}

int	read_piece(t_data *data, t_piece *piece)
{
	char	*seek;
	int		row;
	int		x;

	seek = data->temp + 6;
	piece->height = (int)ft_strtol(seek, &seek);
	piece->width = (int)ft_strtol(seek, &seek);
	if (piece->width <= 0 || piece->height <= 0)
		return (9);
	piece->ptr = (char*)xalloc(data->width * piece->height);
	if (piece->ptr == NULL)
		return (10);
	row = 0;
	while (row < piece->height)
	{
		free(data->temp);
		ft_getline(0, &(data->temp));
		x = -1;
		while (++x < piece->width)
			if (data->temp[x] == '*')
				*(piece->ptr + (row * data->width) + x) = 1;
		row++;
	}
	return (0);
}
