/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_put_something1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:37:50 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:37:51 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/error.h"

int	ft_err_put_int(int n, int *p)
{
	char	c;
	long	long_n;

	long_n = n;
	if (long_n < 0)
	{
		long_n *= -1;
		if (write(2, "-", 1) < 0)
			return (-1);
		(*p)++;
	}
	if (10 <= long_n)
	{
		ft_err_put_int(long_n / 10, p);
	}
	c = long_n % 10 + '0';
	if (*p == -1 || write(2, &c, 1) < 0)
	{
		*p = -1;
		return (-1);
	}
	(*p)++;
	return (*p);
}

int	ft_err_put_unsigned_int(unsigned int n, int *p)
{
	char	c;

	if (10 <= n)
	{
		ft_err_put_unsigned_int(n / 10, p);
	}
	c = n % 10 + '0';
	if (*p == -1 || write(2, &c, 1) < 0)
	{
		*p = -1;
		return (-1);
	}
	(*p)++;
	return (*p);
}
