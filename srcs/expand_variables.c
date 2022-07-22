/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:31:17 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/23 00:12:15 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char	*str)
{
	int		start;
	int		end;

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

void	check_quote_2(char *type, char c)
{
	if (*type == -1 && c == 39)
		*type = c;
	else if (c == *type)
		*type = -1;
}

char	*get_start_unquote(char *str)
{
	int		i;
	char	type;

	type = -1;
	i = 0;
	while (str[i])
	{
		check_quote_2(&type, str[i]);
		if (str[i] == '$' && type == -1)
			break ;
		i++;
	}
	if (!str[i])
		return (NULL);
	if (i > 0 && str[i] == '$')
		return (ft_substr(str, 0, i));
	return (NULL);
}

char	*expand_variables(t_data *data, char *str)
{
	char	type;
	char	*start;
	char	*end;
	int		i;
	char	*tmp;

	i = 0;
	type = -1;
	while (str && str[i])
	{
		check_quote_2(&type, str[i]);
		if (str[i] =='$' && type == -1)
		{
			start = get_start_unquote(str);
			end = replace_variables(ft_substr(str, i, ft_strlen(str) - i), data);
			tmp = str;
			str = ft_strjoin(start, end);
			free(tmp);
			free(start);
			free(end);
		}
		i++;
	}
	return (str);
}
