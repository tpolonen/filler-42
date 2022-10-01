/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:16:16 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/01 20:42:13 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int main(void)
{
	static t_data	data;
	char			*header;
	char			*next;

	(void) data;
	// get which player you are
	ft_getline(0, &header);
	free(header);
	// game loop until opponent dies or moves run out
	while (ft_getline(0, &next)) free(next);
	// suicide
	write(1, "[-3214523 -3463432]\n", 20);
	return (0);
}
