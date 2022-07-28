/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:21 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/28 14:46:50 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args_pwd(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		j = 0;
		if (str[i][0] == '-')
			return (0);
		i++;
	}
	return (1);
}

int	pwd(t_data *data, int ac, char **av)
{
	(void)ac;
	if (!check_args_pwd(av))
	{
		ft_putstr_fd("minishell: pwd: --: invalid option\n", 2);
		return (2);
	}
	if (!data->relative_path)
		return (-1);
	ft_printf("%s\n", data->relative_path);
	return (0);
}
