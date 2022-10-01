/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:31:37 by tpolonen          #+#    #+#             */
/*   Updated: 2022/06/20 10:48:34 by teppo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int nb, int fd)
{
	int	ret;

	ret = 0;
	if (nb < 0)
	{
		if (nb == -2147483648)
			return (ft_putstr_fd("-2147483648", fd));
		ret += ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb > 9)
		ret += ft_putnbr_fd(nb / 10, fd);
	return (ret + ft_putchar_fd((nb % 10) + '0', fd));
}
