/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:21 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/04 03:13:57 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args_pwd(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i][0] == '-')
			return (0);
		i++;
	}
	return (1);
}

int	pwd(t_data *data, int ac, char **av)
{
	char	*pwd;

	(void)ac;
	if (!check_args_pwd(av))
	{
		ft_putstr_fd("minishell: pwd: --: invalid option\n", 2);
		return (2);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		msh_exit(data, 1);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
