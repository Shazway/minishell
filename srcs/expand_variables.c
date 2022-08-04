/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:31:17 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/04 03:05:10 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable_worker(t_data *data, char *str, int *i)
{
	char	*true_var;
	char	*end;
	char	*start;

	true_var = NULL;
	if (!get_start_unquote(str, &start))
		msh_exit(data, 1);
	end = replace_variables(ft_substr(str, *i,
				ft_strlen(str) - *i), data, NULL, &true_var);
	if (!end)
		return (ft_free(start));
	free(str);
	str = ft_strjoin(start, end);
	free(start);
	free(end);
	if (true_var[0])
		*i += ft_strlen(true_var);
	free(true_var);
	return (str);
}

char	*expand_variables(t_data *data, char *str, char type)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		check_quote(&type, str[i]);
		if ((str[i] == '$' && type != '\'') && !is_expand(str[i + 1]))
		{
			str = expand_variable_worker(data, str, &i);
			if (!str)
				return (NULL);
			continue ;
		}
		i++;
	}
	return (str);
}
