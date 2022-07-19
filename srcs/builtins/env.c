/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:28:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/19 22:33:04 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data, int ac)
{
	(void)ac;
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

char	*replace_variables(char	*str, t_data *data)
{
	char	*true_var;
	char	*start;
	char	*end;
	char	*tmp;
	char	*name;

	if (!str)
		return (str);
	start = get_start(str);
	name = get_name(str);
	true_var = get_var(name, data);
	end = get_end(str, ft_strlen(start) + ft_strlen(name));
	tmp = str;
	str = ft_strjoin(start, true_var);
	free(tmp);
	free(start);
	free(true_var);
	tmp = str;
	str = ft_strjoin(str, end);
	free(end);
	free(tmp);
	free(name);
	return (str);
}
