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

int	count(char *ptr, size_t n)
{
	int	ret;

	if (n == 0)
		return (0);
	ret = 0;
	while (n-- > 0)
	{
		if (*(ptr++))
			ret++;
	}
	return (ret);
}

int	comp1(char *ptr1, char *ptr2, size_t n)
{
	while (n-- > 0)
	{
		if (ptr1[n] & ptr2[n])
			return (1);
	}
	return (0);
}

static int	comp2(char *ptr1, char *ptr2, size_t n)
{
	void	*p1;
	void	*p2;

	p1 = ptr1;
	p2 = ptr2;
	while (n >= sizeof(long long) && !(*(long long *)p1 & *(long long *)p2))
	{
		p1 += sizeof(long long);
		p2 += sizeof(long long);
		n -= sizeof(long long);
	}
	while (n >= sizeof(int) && !(*(int *)p1 & *(int *)p2))
	{
		p1 += sizeof(int);
		p2 += sizeof(int);
		n -= sizeof(int);
	}
	return (comp1((char *)p1, (char *)p2, n));
}

int	comp(char *ptr1, char *ptr2, size_t n)
{
	if (n == 0)
		return (0);
	if (n > sizeof(long long))
		return (comp2(ptr1, ptr2, n));
	return (comp1(ptr1, ptr2, n));
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
