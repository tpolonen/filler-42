/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:48:51 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/07 18:28:46 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	make_move(t_data *data, t_piece *piece)
{
	static int	enemy_bits;

	free(data->temp);
	(void)piece;
	(void)enemy_bits;
	data->temp = ft_strdup("0 0\n");
	free(piece->ptr);
	return (1);
}
