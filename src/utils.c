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
	if (data->oboard_ptr)
		ft_memdel((void **)&data->oboard_ptr);
	if (data->xboard_ptr)
		ft_memdel((void **)&data->xboard_ptr);
	if (data->temp)
		ft_memdel((void **)&data->temp);
	if (get_piece()->ptr)
		ft_memdel((void **)&get_piece()->ptr);
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

void	*xalloc(size_t min_size)
{
	size_t	size;
	void	*alloc;

	size = 2;
	while (size < min_size)
		size *= 2;
	alloc = malloc(size);
	if (alloc)
		ft_bzero(alloc, size);
	return (alloc);
}
