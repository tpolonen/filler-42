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

	col = 0;
	ft_putstr("\t");
	while (col < width)
		ft_putchar('0' + (col++ % 10));
	ft_putendl("");
	row = -1;
	while (++row < height)
	{
		col = -1;
		ft_putnbr(row);
		ft_putstr("\t");
		while (++col < width)
		{
			if (ptr[(row * width) + col] == 1)
				ft_putchar('*');
			else if (ptr[(row * width) + col])
				ft_putchar(ptr[(row * width) + col]);
			else
				ft_putchar('.');
		}
		ft_putendl("");
	}
}

static void	fill_debug_board(char *output, t_data *data, t_strat *strat,
		t_dintarr *valid_moves)
{
	const int	size = data->width * data->height;
	int			i;

	i = 0;
	while (i < size)
	{
		if (data->oboard_ptr[i])
			output[i] = 'o';
		else if (data->xboard_ptr[i])
			output[i] = 'x';
		else if (strat->target_ptr[i])
			output[i] = 't';
		else
			output[i] = '.';
		i++;
	}
	i = 0;
	while (i < (int)valid_moves->len)
	{
		output[valid_moves->arr[i]] = 'A' + i;
		i++;
	}
}

static void	print_debug_board(t_data *data, char *output, int width)
{
	int	row;

	row = 0;
	while (row < data->height)
	{
		write(2, output + row * width, width);
		write(2, "\n", 1);
		row++;
	}
}

void	print_valid_moves(t_data *data, t_dintarr *valid_moves)
{
	const int		size = data->width * data->height;
	const int		width = data->width;
	const t_strat	*strat = get_strat();
	const t_dintarr	*target_shape = strat->target_shape;
	char			*output;

	if (strat->victory)
		ft_putstr_fd("\nVICTORY", 2);
	ft_putstr_fd("\nvalid moves len:", 2);
	ft_putnbr_fd(valid_moves->len, 2);
	ft_putstr_fd("\ntarget arr len:", 2);
	ft_putnbr_fd(target_shape->len, 2);
	ft_putchar_fd('\n', 2);
	output = xalloc(size);
	fill_debug_board(output, data, (t_strat *)strat, valid_moves);
	print_debug_board(data, output, width);
	free(output);
}
