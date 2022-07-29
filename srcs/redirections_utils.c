/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 21:44:26 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/29 21:50:25 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rfiles_worker(t_cmd *arg, t_data *data)
{
	int	i;

	i = 0;
	while (arg->args && arg->args[i])
	{
		if (is_redirection(arg->args[i], 0))
		{
			if (!setup_rfiles(arg, i, data))
				msh_exit(data);
			i++;
		}
		if (arg->args[i])
			i++;
	}
}
