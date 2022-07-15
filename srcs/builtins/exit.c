/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:28:23 by tmoragli          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/14 16:58:23 by tmoragli         ###   ########.fr       */
=======
/*   Updated: 2022/07/15 15:03:25 by mdkhissi         ###   ########.fr       */
>>>>>>> execution
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	shell_exit(int ac, char **av)
{
	unsigned char	ret;

	if (check_digits(av))
	{
		printf("exit\nbash: exit: %s: numeric argument required", av[0]);
		exit(2);
	}
	if (ac > 1)
		return (printf("bash: exit: too many arguments\n"));
	printf("exit\n");
	ret = ft_atoi(av[0]);
	exit((int)ret);
	return (1);
}
