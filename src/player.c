/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:48:51 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/08 18:07:13 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_strats	*get_strats(void)
{
	static t_strats	strats;

	return (&strats);
}

int	make_move(t_data *data, t_piece *piece)
{
	t_strats	*strats;

	ft_memdel((void **)&data->temp);
	strats = get_strats();
	if (!strats->victory)
	{
		//check if victory flag should be set
		//make an actual move if possible, otherwise return 0
	}
	else
	{
		data->temp = ft_strdup("0 0\n");
	}
	ft_memdel((void **)&piece->ptr);
	return (1);
}
