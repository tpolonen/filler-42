/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:53:34 by teppo             #+#    #+#             */
/*   Updated: 2022/06/22 23:12:34 by teppo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* putset works similarly to memset - char c is printed count times.
 * This form might be a bit overengineered, but at least it guarantees
 * that larger outputs are printed as fast as possible.
 */

int	ft_putset(int count, char c)
{
	int		ret;
	char	buf[sizeof(size_t)];

	ret = 0;
	ft_memset(buf, c, sizeof(size_t));
	while (count > (int) sizeof(size_t))
	{
		ret += (int)write(1, buf, sizeof(size_t));
		count -= (int) sizeof(size_t);
	}
	while (count > (int) sizeof(int))
	{
		ret += (int)write(1, buf, sizeof(int));
		count -= (int) sizeof(int);
	}
	while (count)
	{
		ret += (int)write(1, buf, 1);
		count -= 1;
	}
	return (ret);
}

