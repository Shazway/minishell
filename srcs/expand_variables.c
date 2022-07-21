/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:31:17 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/21 00:05:12 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char	*str)
{
	int	start;
	int	end;

	start = 0;
	while (str && str[start] && str[start] != '$')
		start++;
	if (str[start] == '$')
		start++;
	end = start;
	while (str && ft_isalnum(str[end]))
		end++;
	if (end > 0)
		end--;
	return (ft_substr(str, start, (end - start + 1)));
}

char	*get_var(char *str, t_data *data)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (data->env_str && data->env_str[i])
	{
		if (!ft_strncmp(str, data->env_str[i], len))
		{
			dest = ft_strdup(ft_strchr(data->env_str[i], '=') + 1);
			return (dest);
		}
		i++;
	}
	return (NULL);
}

char	*get_start(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (NULL);
	if (i > 0 && str[i] == '$')
		return (ft_substr(str, 0, i));
	return (NULL);
}

char	*get_end(char *str, int index)
{
	int	i;

	if (index > (int)ft_strlen(str))
		return (NULL);
	i = index;
	if (!str[i])
		return (NULL);
	i++;
	return (ft_substr(str, i, ft_strlen(str)));
}

void	expand_variables(t_data *data)
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
			while (arg->args[i] && ft_strchr(arg->args[i], '$'))
				arg->args[i] = replace_variables(arg->args[i], data);
			i++;
		}
		str_arr_display(arg->args);
		tmp = tmp->next;
	}
}
