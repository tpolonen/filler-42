/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:57:51 by tpolonen          #+#    #+#             */
/*   Updated: 2022/06/02 17:01:52 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	dstrgrow(t_dstr **ds, ssize_t len)
{
	size_t	new_size;
	char	*new_str;

	new_size = ((*ds)->len + len);
	new_str = (char *) ft_calloc(1, new_size * sizeof(char));
	if (!new_str)
		return (-1);
	ft_memcpy((void *)new_str, (void *)(*ds)->str, (*ds)->len);
	free((*ds)->str);
	(*ds)->str = new_str;
	(*ds)->alloced = new_size;
	return ((size_t)new_size);
}

ssize_t	ft_dstrnew(t_dstr **ds, size_t len)
{
	*ds = (t_dstr *) ft_calloc(1, sizeof(t_dstr));
	if (!*ds)
		return (-1);
	(*ds)->str = (char *) ft_calloc(len, sizeof(char));
	if (!(*ds)->str)
	{
		ft_memdel((void **)ds);
		return (-1);
	}
	(*ds)->len = 0;
	(*ds)->alloced = len;
	return (len);
}

ssize_t	ft_dstraddc(t_dstr **ds, const char c)
{
	if (*ds == NULL)
		ft_dstrnew(ds, 8);
	else if ((*ds)->alloced < (*ds)->len + 1)
	{
		if (dstrgrow(ds, (*ds)->len * 2) < 0)
			return (-1);
	}
	(*ds)->str[(*ds)->len] = c;
	(*ds)->len++;
	return ((*ds)->len);
}

ssize_t	ft_dstrbuild(t_dstr **ds, const char *str, size_t len)
{
	if (*ds == NULL)
		ft_dstrnew(ds, len);
	else if ((*ds)->alloced < (*ds)->len + len + 1)
	{
		if (dstrgrow(ds, ((*ds)->len + len) * 2) < 0)
			return (-1);
	}
	ft_memcpy((void *)((*ds)->str + (*ds)->len), (void *)str, len);
	(*ds)->len += len;
	return ((ssize_t)(*ds)->len);
}

ssize_t	ft_dstrclose(t_dstr **ds, char **target)
{
	int	ret;

	ret = 0;
	if (*ds == NULL)
		return (ret);
	ret = (*ds)->len;
	if (target != NULL)
	{
		if ((*ds)->alloced == (*ds)->len + 1)
			*target = (*ds)->str;
		else
		{
			*target = ft_strnew((*ds)->len);
			if (target)
				ft_memcpy(*target, (*ds)->str, (*ds)->len);
			else
				ret = -1;
			free((*ds)->str);
		}
	}
	else
		free((*ds)->str);
	ft_memdel((void **) ds);
	return (ret);
}
