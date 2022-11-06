/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:48:58 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/07 18:34:17 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	debug_print(char *ptr, int width, int height)
{
	int	row;
	int	col;

	row = 0;
	while (row < height)
	{
		col = 0;
		ft_putnbr(row);
		ft_putstr("\t");
		while (col < width)
		{
			if (ptr[(row * width) + col] == 1)
				ft_putchar('*');
			else if (ptr[(row * width) + col])
				ft_putchar('?');
			else
				ft_putchar('.');
			col++;
		}
		ft_putendl("");
		row++;
	}
}
