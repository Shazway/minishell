/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 21:44:26 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/01 01:42:07 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rfiles_worker(t_cmd *arg, t_data *data)
{
	int	i;

	i = 0;
	while (arg->args && arg->args[i])
	{
		if (is_redirection(arg->args[i], 0))
		{
			if (is_redirection(arg->args[i + 1], 0))
			{
				ft_putstr_fd("minishell: syntax error near > or <\n", 2);
				return (1);
			}
			if (!setup_rfiles(arg, i, data))
				msh_exit(data, 1);
			i++;
		}
		if (arg->args[i])
			i++;
	}
	return (0);
}
