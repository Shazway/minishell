/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:28:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/02 17:46:50 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

static long long	x_sign_l(long long x, int sign)
{
	if (sign < 0)
		x = 0;
	else
		x = -1;
	return (x);
}

long	ft_atol(const char *str)
{
	int			i;
	long long	x;
	int			sign;

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
		if (x * sign > LONG_MAX || x * sign < LONG_MIN)
		{
			x = x_sign_l(x, sign);
			break ;
		}
		i++;
	}
	return ((long)(x * sign));
}

int	check_digits(char *str)
{
	int		i;
	int		count;
	char	sign;

	i = 0;
	sign = '+';
	count = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		sign = str[i];
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		count++;
		i++;
	}
	if (str[i] != '\0')
		return (1);
	if (count > 19)
		return (1);
	if ((sign == '+' && i > 0 && count == 19 && str[i - 1] > '7')
		|| (sign == '-' && i > 0 && count == 19 && str[i - 1] > '8'))
		return (1);
	return (0);
}

int	shell_exit(t_data *data, int ac, char **av)
{
	long	arg;

	(void)data;
	if (ac == 1)
		return (0);
	if (check_digits(av[1]))
		return (2);
	if (ac > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (257);
	}
	arg = ft_atol(av[1]);
	return (arg % 256);
}
