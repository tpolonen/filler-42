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

static int	can_make_move(t_data *data, int *error)
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
	if (!can_read_board(data) || !can_read_piece(data, get_piece()))
	{
		*error = 10;
		return (0);
	}
	strategize(data);
	return (valid_move_exists());
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
	error = init_data(data);
	if (error)
		return (clean_exit(data, "Error in map header: ", error));
	while (can_make_move(data, &error))
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
