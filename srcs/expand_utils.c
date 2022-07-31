/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 21:01:39 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/31 23:37:10 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char	*str, char type)
{
	int		start;
	int		end;

	start = 0;
	while (str && str[start] && str[start] != '$')
		start++;
	if (str[start] == '$')
		start++;
	end = start;
	if (str && str[end] == '?')
		return (ft_strdup("?"));
	while (str && str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	if (type == -1 && (str[end] == '"' || str[end] == '\''))
		return (ft_strdup("\0"));
	if (end == start)
		return (ft_strdup("$"));
	if (end > 0)
		end--;
	return (ft_substr(str, start, (end - start + 1)));
}

char	*get_var(char *str, t_data *data)
{
	char	*dest;
	int		i;
	int		len;
	int		var_len;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (!ft_strncmp(str, "$", len))
		return (ft_strdup("$"));
	if (!ft_strncmp(str, "?", len))
		return (ft_itoa(g_cmd_status));
	while (data->env_str && data->env_str[i])
	{
		var_len = ft_strchr(data->env_str[i], '=') - &data->env_str[i][0];
		if ((var_len == len) && !ft_strncmp(data->env_str[i], str, len))
		{
			dest = ft_strdup(ft_strchr(data->env_str[i], '=') + 1);
			return (dest);
		}
		i++;
	}
	return (ft_strdup("\0"));
}

char	*get_end(char *str, int index)
{
	if (index > (int)ft_strlen(str))
		return (ft_strdup("\0"));
	if (!str[index])
		return (ft_strdup("\0"));
	return (ft_substr(str, index, ft_strlen(str) - index));
}

int	get_start_unquote(char *str, char **start)
{
	int		i;
	char	type;

	type = -1;
	i = 0;
	while (str && str[i])
	{
		check_quote(&type, str[i]);
		if ((str[i] == '$' && type != '\''))
			break ;
		i++;
	}
	if (str[i] && i > 0 && str[i] == '$')
	{
		*start = ft_substr(str, 0, i);
		if (!*start)
			return (0);
		return (1);
	}
	*start = ft_strdup("");
	if (!start)
		return (ft_free(start) != 0);
	return (1);
}
