/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 21:01:39 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/29 22:28:58 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char	*str, char type)
{
	int		start;
	int		end;

	start = 0;
	while (str && str[start] && str[start] != '$')
	{
		start++;
	}
	if (str[start] == '$')
		start++;
	end = start;
	if (str && str[end] == '?')
		return (ft_strdup("$?"));
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

	i = 0;
	if (!str)
		return (NULL);
	if (!ft_strncmp(str, "$", ft_strlen(str)))
		return (ft_strdup("$"));
	if (!ft_strncmp(str, "$?", ft_strlen(str)))
		return (ft_itoa(g_cmd_status));
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
	return (ft_strdup("\0"));
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
	return (ft_substr(str, i, ft_strlen(str) - i));
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
	return (1);
}
