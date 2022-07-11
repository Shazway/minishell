/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:42 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/11 15:38:03 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *data, t_cmd *cmd)
{
	int		i;
	int		j;
	int		len;
	char	*p_eq;
	char	**entry;

	if (cmd->ac == 1)
		ft_env(data, cmd);
	else
	{
		entry = malloc((cmd->ac - 1) * sizeof(char *));
		i = 1;
		j = 0;
		while (i < cmd->ac)
		{
			p_eq = ft_strchr(cmd->args[i], '=');
			if (!p_eq)
				len = ft_strlen(cmd->args[i]);
			else
				len = p_eq - &cmd->args[i][0];
			if (is_validid(cmd->args[i], len) && p_eq)
			{
				entry[j] = cmd->args[i];
				j++;
			}
			else if (!is_validid(cmd->args[i], len) && p_eq)
				printf("minishell: export: `%s': not a valid identifier\n", cmd->args[i]);
			i++;
		}
		update_env(data, entry, j);
	}
}

int	is_validid(char	*identifier, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!(ft_isalnum(identifier[i]) && identifier[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
