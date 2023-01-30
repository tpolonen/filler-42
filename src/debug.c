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
	print_debug_piece(get_piece());
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

void	print_debug_choice(int hit, int score, const char *type)
{
	ft_putchar_fd('A' + hit, 2);
	ft_putstr_fd(" was chosen for it's ", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(" with score of ", 2);
	ft_putnbr_fd(score, 2);
	ft_putendl_fd("", 2);
}

void	print_debug_piece(t_piece *piece)
{
	const int	width = get_data()->width;
	const int	height = piece->rect.y2 - piece->rect.y1 + 1;
	char		output[1024];
	int			i;	

	ft_memset((void *)output, '.', sizeof(output));
	i = 0;
	while (i < (int)piece->shape->len)
		output[piece->shape->arr[i++]] = '*';
	ft_putendl_fd("\nPiece:", 2);
	i = 0;
	while (i < height)
	{
		write(2, output + i * width, piece->rect.x2 - piece->rect.x1 + 1);
		write(2, "\n", 1);
		i++;
	}
}
