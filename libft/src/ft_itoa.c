/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:49:02 by tpolonen          #+#    #+#             */
/*   Updated: 2021/12/13 14:11:05 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n, int base)
{
	size_t	len;
	char	*str;

	len = ft_intlen(n, base);
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_tobase(n, base, str);
	return (str);
}
