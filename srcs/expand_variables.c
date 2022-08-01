/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:31:17 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/01 15:38:03 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variables(t_data *data, char *str, char type)
{
	char	*start;
	char	*end;
	int		i;

	i = 0;
	while (str && str[i])
	{
		check_quote(&type, str[i]);
		if ((str[i] == '$' && type != '\'') && !is_expand(str[i + 1]))
		{
			if (!get_start_unquote(str, &start))
				msh_exit(data, 1);
			end = replace_variables(ft_substr(str, i,
						ft_strlen(str) - i), data, NULL);
			if (!end)
				return (ft_free(start));
			free(str);
			str = ft_strjoin(start, end);
			free(start);
			free(end);
			if (!str)
				return (NULL);
		}
		if (!str[i])
			return (str);
		i++;
	}
	return (str);
}
