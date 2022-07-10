/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:28:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/11 00:37:54 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     set_env(t_data *data)
{
	data->env_str = str_arr_add(__environ, NULL, 0);
	if (!data->env_str)
		return (1);
	else
		return (0);
}

int		update_env(t_data *data, char **entry, int len_entry)
{
	char **old_envr;

	old_envr = data->env_str;
	data->env_str = str_arr_add(data->env_str, entry, len_entry);
	str_arr_free(old_envr);
	if (!data->env_str)
		return (1);
	else
		return (0);
}

void	ft_env(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
}