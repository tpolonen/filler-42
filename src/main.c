/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:16:16 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/06 17:11:59 by tpolonen         ###   ########.fr       */
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
	free(data->temp);
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
	free(data->temp);
	data->oboard_ptr = (char *)xalloc(data->width * data->height);
	data->xboard_ptr = (char *)xalloc(data->width * data->height);
	if (data->oboard_ptr == NULL || data->xboard_ptr == NULL)
		return (7);
	return ((data->width <= 0) || (data->height <= 0));
}

static int	get_turn(t_data *data, int *error, FILE *debug)
{
	t_piece	piece;

	(void)debug;
	ft_getline(0, &(data->temp));
	while (ft_strncmp(data->temp, "000", 3) != 0)
	{
		free(data->temp);
		ft_getline(0, &(data->temp));
	}
	*error = read_board(data);
	if (*error)
		return (0);
//	debug_print(data->oboard_ptr, data->width, data->height);
//	debug_print(data->xboard_ptr, data->width, data->height);
	*error = read_piece(data, &piece);
	if (*error)
		return (0);
//	debug_print(piece.ptr, data->width, piece.height);
	//make a move...
	return (0);
}

static int	clean_exit(t_data *data, const char *str, int error)
{
	if (data->oboard_ptr)
		free(data->oboard_ptr);
	if (data->oboard_ptr)
		free(data->xboard_ptr);
	if (data->temp)
		free(data->temp);
	if (str)
		ft_putstr(str);
	if (error)
		ft_putnbr(error);
	ft_putendl("");
	return (error);
}

int main(void)
{
	static t_data	data;
	FILE			*debug;
	int				error;

	debug = fopen(".last", "w");
	ft_getline(0, &(data.temp));
	error = set_player(&data);
	if (error)
		return (clean_exit(&data, "Error in player data: ", error));
	ft_getline(0, &(data.temp));
	error = init_data(&data);
	if (error)
		return (clean_exit(&data, "Error in map header: ", error));
	while (get_turn(&data, &error, debug))
	{
		if (data.temp)
		{
			ft_putendl(data.temp);
			free(data.temp);
		}
	}
	fprintf(debug, "END\n");
	fclose(debug);
	if (error)
		return (clean_exit(&data, "Error in processing turn: ", error));
	return (clean_exit(&data, "42 42", 0));
}
