/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:00:08 by tpolonen          #+#    #+#             */
/*   Updated: 2022/06/17 19:12:50 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

long long	ft_llabs(long long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

size_t	ft_ssabs(ssize_t n)
{
	if (n < 0)
		return ((size_t)(n * -1));
	return (n);
}
