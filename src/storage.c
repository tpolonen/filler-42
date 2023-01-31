/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:39:19 by tpolonen          #+#    #+#             */
/*   Updated: 2023/01/31 19:17:09 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_strat	*get_strat(void)
{
	static t_strat	strat;

	return (&strat);
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

t_piece	*get_piece(void)
{
	static t_piece	piece;

	return (&piece);
}

t_tactics	*get_tactics(void)
{
	static t_tactics	tactics;

	return (&tactics);
}
