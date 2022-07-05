/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:45:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/05 20:19:11 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(int ac, char **av)
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

char	*pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	return (path);
}

int		is_double_dot(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '.')
		i++;
	if (i == 2 && str[i] == '\0')
		return (1);
	return (0);
}
