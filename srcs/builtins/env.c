/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:28:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/29 00:25:32 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, int ac, char **av)
{
	(void)ac;
	(void)av;
	if (ac > 1)
		return (0);
	str_arr_display(data->env_str);
	return (0);
}

int	set_env(t_data *data)
{
	int	i;
	int	size;

	i = 0;
	size = str_arr_size(__environ);
	data->env_str = malloc(sizeof(char *) * (size + 1));
	if (!data->env_str)
		return (0);
	data->env_str[size] = NULL;
	while (__environ && __environ[i])
	{
		data->env_str[i] = ft_strdup(__environ[i]);
		if (!data->env_str[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_s_replace(char *dest, char *src)
{
	char	*tmp;

	tmp = dest;
	dest = src;
	free(tmp);
	return (dest);
}

char	*find_var(char **envr, char *entry)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(entry);
	if (!entry)
		return (NULL);
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
	end = NULL;
	start = get_start(str);
	name = get_name(str);
	if (!name)
		true_var = get_var(NULL, data);
	else if (!ft_strncmp(name, "$", ft_strlen(name)))
	{
		true_var = ft_strdup("$");
		end = get_end(str, ft_strlen(name));
	}
	else
	{
		true_var = get_var(name, data);
		end = get_end(str, ft_strlen(name) + 1);
	}
	printf("start[%s]value[%s]end[%s]\n", name, true_var, end);
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
