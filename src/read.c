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

int	read_board(t_data *data)
{
	int	row;

	row = 0;
	while (row < data->height)
	{
		//copy data from temp to oboard_ptr...
		//copy data from temp to xboard_ptr...
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
	
	seek = data->temp + 6;
	piece->width = (int)ft_strtol(seek, &seek);
	piece->height = (int)ft_strtol(seek, &seek);
	if (piece->width <= 0 || piece->height <= 0)
		return (9);
	piece->ptr = xalloc(piece->width * piece->height);
	if (piece->ptr == NULL)
		return (10);
	row = 0;
	while (row < piece->height)
	{
		free(data->temp);
		ft_getline(0, &(data->temp));
		row++;
	}
	return (0);
}
