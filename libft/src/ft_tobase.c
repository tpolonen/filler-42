/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tobase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:44:01 by tpolonen          #+#    #+#             */
/*   Updated: 2022/12/15 18:44:03 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Takes a number and converts it to char array at the memory address pointed
 * by ptr. Caller should make sure that there actually exists enough allocated
 * memory in that address, can't be arsed to make this memory safe atm.
 * Returns a pointer to a position AFTER the last char.
 */

char	*ft_tobase(int n, int base, char *ptr)
{
	size_t	len;
	size_t	i;

	len = ft_intlen(n, base);
	i = len;
	ptr[i--] = '\0';
	if (n == 0)
		return (ft_strcpy(ptr, "0"));
	while (n != 0)
	{
		ptr[i--] = '0' + (char)(ft_abs(n % base));
		n /= 10;
	}
	if (i == 0)
		ptr[i] = '-';
	return (ptr + len);
}
