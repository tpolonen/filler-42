/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:57:33 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 20:00:35 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_dintarr	*floodfill(char *board, int start, size_t steps, int stop)
{
	const int 	dirs[4][2]  = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	t_dintarr			*explored;

	explored = NULL;
	(void)board;
	(void)dirs;
	(void)start;
	(void)steps;
	(void)stop;

	return(explored);
}
