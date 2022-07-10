/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:11 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/11 01:02:21 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_n(char *str)
{
	int i;

	i = 0;
	if (str[i] != '-')
		return (1);
	while (str && str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	echo(int ac, char **av)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 0;
	if (ac == 1)
		return(write(1, "\n", 1));
	while (av && av[i])
	{
		if (check_echo_n(av[i]))
			ft_putstr_fd(av[i], 1);
		else
			new_line = 0;
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}

