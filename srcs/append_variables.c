/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:31:17 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/18 23:30:56 by tmoragli         ###   ########.fr       */
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
	return (ft_substr(str, start, end));
}
char	*get_var(char *str, t_data *data)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	printf("Variable to search is %s\n", str);
	while (data->env_str && data->env_str[i])
	{
		if (!ft_strncmp(str, data->env_str[i], len))
		{
			dest = ft_strdup(ft_strchr(data->env_str[i], '=') + 1);
			printf("found var, %s\n", dest);
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
	printf("END OF START IS %c\n", str[i]);
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

char	*replace_variables(char	*str, t_data *data, int i)
{
	char	*true_var;
	char	*start;
	char	*end;
	char	*tmp;
	char	*name;

	i = 0;
	printf("STR is : %s\n", str);
	if (!str)
		return (str);
	start = get_start(str);
	name = get_name(str);
	true_var = get_var(name, data);
	end = get_end(str, ft_strlen(start) + ft_strlen(name));
	printf("[END IS %s]\n", end);
	tmp = str;
	str = ft_strjoin(start, true_var);
	printf("Result of first join ([%s][%s])is : %s\n", start, true_var, str);
	free(tmp);
	free(start);
	free(true_var);
	tmp = str;
	str = ft_strjoin(str, end);
	printf("Result of final join is : %s\n", str);
	free(end);
	free(tmp);
	free(name);
	return (str);
}

void	append_variables(t_data *data)
{
	int		i;
	t_cmd	*arg;
	t_list	*tmp;
	int j;
	j = 0;
	tmp = data->cmd;
	while (tmp)
	{
		arg = tmp->content;
		i = 0;
		while (arg->args && arg->args[i])
		{
			while (ft_strchr(arg->args[i], '$') && j < 5)
			{
				arg->args[i] = replace_variables(arg->args[i], data, i);
				j++;
			}
			i++;
		}
		str_arr_display(arg->args);
		tmp = tmp->next;
	}
}
