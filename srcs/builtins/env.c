/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:28:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/18 17:48:03 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data, int ac)
{
		printf("im ac %d\n", ac);
		str_arr_display(data->env_str);
}

int	set_env(t_data *data)
{
	data->env_str = str_arr_add(__environ, NULL, 0);
	if (!data->env_str)
		return (1);
	else
		return (0);
}

int	update_env(t_data *data, char **entry, int len_entry)
{
	char	**old_envr;

	old_envr = data->env_str;
	data->env_str = str_arr_add(data->env_str, entry, len_entry);
	str_arr_free(old_envr);
	if (!data->env_str)
		return (1);
	else
		return (0);
}

char	*find_var(char **envr, char *entry)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(entry);
	while (envr[++i])
		if (!strncmp(envr[i], entry, len))
			return (ft_strdup(envr[i] + len + 1));
	return (NULL);
}