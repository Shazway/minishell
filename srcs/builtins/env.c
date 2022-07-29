/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:28:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/29 22:47:56 by mdkhissi         ###   ########.fr       */
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
	data->env_str = malloc((size + 1) * sizeof(char *));
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

char	*replace_variables(char	*str, t_data *data, char type)
{
	char	*true_var;
	char	*start;
	char	*end;
	char	*tmp;
	char	*name;

	if (!str)
		return (str);
	printf("recieved : [%s] and type is [%c]\n", str, type);
	end = NULL;
	start = get_start(str);
	name = get_name(str, type);
	if (name)
	{
		true_var = get_var(name, data);
		if (ft_strlen(name) == 1)
			end = get_end(str, ft_strlen(name));
		else
			end = get_end(str, ft_strlen(name) + 1);
	}
	else
	{
		true_var = get_var(name, data);
		end = get_end(str, ft_strlen(name) + 1);
	}
	tmp = str;
	str = ft_strjoin(start, true_var);
	ft_free_strs(&tmp, &start, &true_var, NULL);
	tmp = str;
	str = ft_strjoin(str, end);
	ft_free_strs(&end, &tmp, &name, NULL);
	return (str);
}
