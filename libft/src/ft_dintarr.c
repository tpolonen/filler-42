/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dintarr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:20:05 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/01 20:12:38 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

ssize_t	ft_dintarr_create(t_dintarr **darr, size_t size, const char *name)
{
	//ft_putstr_fd("dintarr create\n", 2);
	if (!darr)
		darr = (t_dintarr **)ft_memalloc(sizeof(t_dintarr *));
	*darr = (t_dintarr *)ft_memalloc(sizeof(t_dintarr));
	if (!(*darr))
		return (0);
	(*darr)->arr = (int *)ft_memalloc(sizeof(int) * size);
	dprintf(2, "%s: (*darr):%p new arr:%p\n", name, (*darr), (*darr)->arr);
	if (!(*darr)->arr)
	{
		free(*darr);
		return (0);
	}
	/*
	ft_putstr_fd("(*darr)->arr:", 2);
	ft_putnbr_fd((int)(size_t)(*darr)->arr, 2);
	ft_putstr_fd("\n", 2);
	*/
	ft_strlcat((char *)(*darr)->name, name, 32);
	(*darr)->len = 0;
	(*darr)->alloced = sizeof(int) * size;
	return (size);
}

ssize_t	ft_dintarr_add(t_dintarr **darr, const int n)
{
	int		*n_arr;
	size_t	n_size;

	if (darr == NULL || *darr == NULL)
	{
		if (!ft_dintarr_create(darr, DINT_DEF_SIZE, "New"))
			return (-1);
	}
	else if ((*darr)->alloced < (((*darr)->len + 1)) * sizeof(int))
	{
/*		ft_putstr_fd("expanding (*darr):", 2);
		ft_putnbr_fd((int)(size_t)(*darr), 2);
		ft_putstr_fd(" arr:", 2);
		ft_putnbr_fd((int)(size_t)(*darr)->arr, 2);
		*/
		n_size = 2;
		while (n_size < 2 * (*darr)->alloced)
			n_size *= 2;
		n_arr = (int *) ft_memalloc(n_size);
		if (!n_arr)
			return (-1);
		/*
		ft_putstr_fd(" n_arr:", 2);
		ft_putnbr_fd((int)(size_t)n_arr, 2);
		ft_putstr_fd("\n", 2);
		*/
		ft_memcpy((void *)n_arr, (void *)(*darr)->arr,
			(((*darr)->len) * sizeof(int)));
		free((*darr)->arr);
		(*darr)->arr = n_arr;
		(*darr)->alloced = n_size;
		dprintf(2, "%s: (*darr):%p new arr:%p\n", (*darr)->name, (*darr), (*darr)->arr);
	}
	(*darr)->arr[(*darr)->len] = n;
	(*darr)->len++;
	return ((size_t)(*darr)->len);
}

ssize_t	ft_dintarr_close(t_dintarr **src, int **dst)
{
	ssize_t	ret;

	ret = 1;
	if (src == NULL || *src == NULL)
		return (0);
	dprintf(2, "%s (*src)?%d (*src):%p (*src)->arr:%p len:%zu alloced:%zu\n",
			(*src)->name,
			(*src) != NULL, (*src), (*src)->arr, 
			(*src)->len, (*src)->alloced);
	if (dst != NULL)
	{
		if ((*src)->alloced == (*src)->len * sizeof(int))
			*dst = (*src)->arr;
		else
		{
			*dst = (int *) ft_memalloc((*src)->len * sizeof(int));
			if (dst)
				ft_memcpy(*dst, (*src)->arr, (*src)->len * sizeof(int));
			else
				ret = 0;
			free((*src)->arr);
		}
	}
	else if ((*src)->arr)
		ft_memdel((void **)&(*src)->arr);
	ft_memdel((void **) src);
	return (ret);
}

ssize_t	ft_dintarr_clear(t_dintarr **darr)
{
	//ft_putstr_fd("dintarr clear\n", 2);
	if (!*darr)
		return (0);
	ft_bzero((void *)(*darr)->arr, (*darr)->alloced);
	(*darr)->len = 0;
	return (1);
}
