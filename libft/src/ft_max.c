/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:21:17 by tpolonen          #+#    #+#             */
/*   Updated: 2021/11/24 17:36:28 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

size_t	ft_smax(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

size_t	ft_smin(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}
