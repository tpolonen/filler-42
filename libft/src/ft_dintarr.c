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

ssize_t	ft_dintarr_create(t_dintarr **darr, size_t size, const char *name)
{
	if (!darr)
		darr = (t_dintarr **)ft_memalloc(sizeof(t_dintarr *));
	*darr = (t_dintarr *)ft_memalloc(sizeof(t_dintarr));
	if (!(*darr))
		return (0);
	(*darr)->arr = (int *)ft_memalloc(sizeof(int) * size);
	if (!(*darr)->arr)
	{
		free(*darr);
		return (0);
	}
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
		n_size = 2;
		while (n_size < 2 * (*darr)->alloced)
			n_size *= 2;
		n_arr = (int *) ft_memalloc(n_size);
		if (!n_arr)
			return (-1);
		ft_memcpy((void *)n_arr, (void *)(*darr)->arr,
			(((*darr)->len) * sizeof(int)));
		free((*darr)->arr);
		(*darr)->arr = n_arr;
		(*darr)->alloced = n_size;
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
	if (!*darr)
		return (0);
	ft_bzero((void *)(*darr)->arr, (*darr)->alloced);
	(*darr)->len = 0;
	return (1);
}
