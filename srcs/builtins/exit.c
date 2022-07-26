/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:28:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/26 17:45:35 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(int c)
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

int	ft_atol(const char *str)
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

int	check_digits(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		j = 0;
		if (str[i][j] && (str[i][j] == '-' || str[i][j] == '+'))
			i++;
		while (str[i][j] && str[i][j] >= '0' && str[i][j] <= '9')
			j++;
		if (str[i][j] != '\0')
			return (1);
		i++;
	}
	return (0);
}

int	shell_exit(t_data *data, int ac, char **av)
{
	long	arg;

	(void)data;
	if (ac == 1)
	{
		write(1, "exit\n", 6);
		exit(EXIT_SUCCESS);
	}
	if (check_digits(av))
	{
		ft_printf("exit\nbash: exit: %s: numeric argument required\n", av[0]);
		exit(2);
	}
	if (ac > 1)
	{
		write(1, "bash: exit: too many arguments\n", 32);
		return (1);
	}
	write(1, "exit\n", 6);
	arg = ft_atol(av[0]);
	exit(arg % 256);
	return (1);
}
