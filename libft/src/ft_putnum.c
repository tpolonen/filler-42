/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:54:51 by teppo             #+#    #+#             */
/*   Updated: 2022/06/22 23:10:12 by teppo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Expanded version of the stock ft_putbnr, original preserved for portability.
 * ft_putnum assembles the number as a string to buffer and outputs it.
 * If the minimum length is longer than amount of digits in number,
 * desired amount of zeroes is printed first and the buffer afterwards.
 */

int	ft_putnum(size_t num, int base, int min_len, int all_caps)
{
	int			len;
	char		*digits;
	char		buf[30];
	int			i;
	int			ret;

	ret = 0;
	len = (int)ft_sizelen(num, base);
	if (len < min_len)
		ret += ft_putset(min_len - len, '0');
	i = len;
	if (all_caps)
		digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	else
		digits = "0123456789abcdefghjiklmnopqrstuvwxyz";
	while (i > 0)
	{
		buf[--i] = digits[num % (size_t)base];
		num /= (size_t)base;
	}
	return (ret + (int)write(1, buf, (size_t)len));
}

/* Signed version of putnum for completeness's sake.
 */

int	ft_putnums(ssize_t num, int base, int min_len, int all_caps)
{
	int			len;
	char		*digits;
	char		buf[30];
	int			i;
	int			ret;

	ret = 0;
	len = (int)ft_sizelen(num, base);
	ret += write(1, "-", num < 0);
	num = ft_ssabs(num);
	if (len < min_len)
		ret += ft_putset(min_len - len, '0');
	i = len;
	if (all_caps)
		digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	else
		digits = "0123456789abcdefghjiklmnopqrstuvwxyz";
	while (i > 0)
	{
		buf[--i] = digits[num % (size_t)base];
		num /= (size_t)base;
	}
	return (ret + (int)write(1, buf, (size_t)len));
}
