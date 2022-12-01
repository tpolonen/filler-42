/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:29:40 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/12 17:38:41 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	clean_exit(t_data *data, const char *str, int error)
{
	ft_memdel((void **)&data->xboard_ptr);
	ft_memdel((void **)&data->oboard_ptr);
	ft_memdel((void **)&data->xoboard_ptr);
	ft_memdel((void **)&data->temp);
	ft_memdel((void **)&get_piece()->ptr);
	ft_dintarr_close(get_enemy_shape(), NULL)
	if (str)
		ft_putstr(str);
	if (error)
		ft_putnbr(error);
	ft_putendl("");
	return (error);
}

int	count(char *ptr, size_t n)
{
	int ret;

	ret = 0;
	while (n > 0)
	{
		ret += *ptr & 1;
		ptr++;
		n--;
	}
	return (ret);
}

int	is_cell_filled(int cell)
{
	return (get_strat()->enemy[cell] | get_strat()->player[cell]);
}

void	find_margins(void)
{
	const t_piece	*piece = get_piece();
	const t_dintarr	*shape = piece->shape;
	size_t	i;

	piece->margin->top = shape->arr[0] / piece->width;
	piece->margin->bottom = shape->arr[piece->shape->len - 1] / piece->width;
	piece->margin->left = piece->width - 1;
	piece->margin->right = 0;
	i = 0;
	while (i < shape->len)
	{
		if (shape->arr[i] % piece->width < piece->margin->left)
			piece->margin->left = shape->arr[i] / piece->width;
		if (shape->arr[i] % piece->width > piece->margin->right)
			piece->margin->right = piece->width - shape->arr[i] % piece->width;
	}
}

void	*xalloc(size_t min_size)
{
	size_t	size;
	void	*alloc;

	size = 2;
	while (size < min_size)
		size *= 2;
	alloc = malloc(size);
	if (!alloc)
		clean_exit(get_data(), "Allocation failed", 0);
	ft_bzero(alloc, size);
	return (alloc);
}
