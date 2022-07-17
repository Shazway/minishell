/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:31:17 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/17 21:23:57 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *str, t_data *data)
{
	char	*dest;
	int		i;
	int		len;

	len = ft_strlen(str);
	i = 0;
	dest = NULL;
	while (data->env_str && data->env_str[i])
	{
		if (!ft_strncmp(str, data->env_str[i], len))
		{
			dest = ft_strdup(*(data->env_str) + len);
			break ;
		}
		i++;
	}
	free(str);
	if (!data->env_str[i])
		return (NULL);
	return (dest);
}

char	*replace_variables(char	*str, t_data *data, int i)
{
	char	*end;
	char	*trash;
	char	*start;
	char	*true_var;
	int		dollar_index;

	i = 0;
	while (str && str[i] && str[i] != '$')
		i++;
	if (!str || !str[i])
		return (str);
	start = ft_substr(str, 0, i);
	dollar_index = i;
	while (str[i] && str[i] != ' ' &&
			str[i] != '\t' && str[i] != '\f' &&
			str[i] != '\n' && str[i] != '\r' && str[i] != '\v')
		i++;
	end = ft_substr(str, i, ft_strlen(str));
	trash = str;
	true_var = get_var(ft_substr(str, dollar_index + 1, i), data);
	str = ft_strjoin(start, true_var);
	free(trash);
	free(true_var);
	free(start);
	trash = str;
	str = ft_strjoin(str, end);
	free(trash);
	free(end);
	if (!str)
		return (NULL);
	return (str);
}

void	append_variables(t_data *data)
{
	int		i;
	t_cmd	*arg;
	t_list	*tmp;
	
	tmp = data->cmd;
	while (tmp)
	{
		arg = tmp->content;
		i = 0;
		while (arg->args && arg->args[i])
		{
			arg->args[i] = replace_variables(arg->args[i], data, i);
			i++;
		}
		str_arr_display(arg->args);
		tmp = tmp->next;
	}
}
