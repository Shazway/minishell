/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:42 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/10 20:30:36 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**new_env;
	char	*eq;
	int		len;
	int		j;

	if (cmd->ac == 1)
		ft_env(data, cmd);
	else
	{
		i = 1;
		while (i < cmd->ac)
		{
			eq = ft_strchr(cmd->args[i], '=');
			if (!eq)
				len = ft_strlen(cmd->args[i]);
			else
				len = eq - cmd->args[i][0];
			j = 0;
			while (j < len)
			{
				if (!(ft_isalnum(cmd->args[i][j]) && cmd->args[i][j] == '_'))
					break ;
				j++;
			}
			ft_strdup(cmd->args[i]);
		}
	}
}
