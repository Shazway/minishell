/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:35:38 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/30 18:58:42 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

static long	x_sign(long x, int sign)
{
	if (sign < 0)
		x = 0;
	else
		x = -1;
	return (x);
}

/*
** Bypassing spaces first, if there is a sign after,
** we affect sign variable,
** then we read number by number.
*/

int	ft_atoi(const char *str)
{
	int		i;
	long	x;
	int		sign;

	i = 0;
	x = 0;
	sign = 1;
	while (ft_isspace(str[i]) && str[i])
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	while (ft_isdigit(str[i]) && str[i])
	{
		x = x * 10 + str[i] - '0';
		if (x * sign > INT_MAX || x * sign < INT_MIN)
		{
			x = x_sign(x, sign);
			break ;
		}
		i++;
	}
	return ((int)(x * sign));
}
