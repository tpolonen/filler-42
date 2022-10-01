/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fabs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:25:10 by teppo             #+#    #+#             */
/*   Updated: 2022/06/24 17:31:52 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_fabsf(float n)
{
	if (1.0 / n == -1.0 / 0.0)
		return (0.0);
	if (n < 0.0)
		return (n * -1.0);
	return (n);
}

double	ft_fabs(double n)
{
	if (1.0 / n == -1.0 / 0.0)
		return (0.0);
	if (n < 0.0)
		return (n * -1.0);
	return (n);
}

long double	ft_fabsl(long double n)
{
	if (1.0 / n == -1.0 / 0.0)
		return (0.0);
	if (n < 0.0)
		return (n * -1.0);
	return (n);
}
