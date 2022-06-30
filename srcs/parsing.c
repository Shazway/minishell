/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:59:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/05/07 19:40:46 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes(char *str, int i)
{
	if (i == 0)
		if (str[i + 1] != '|')
			return (0);
	if (i == (int)ft_strlen(str))
		if (str[i - 1] != '|')
			return (0);
	if (str[i + 1] != '|' && str[i - 1] != '|')
		return (0);
	return (1);
}

int	parsing(t_data *data)
{
	int i = 0;
	data->entry = ft_strtrim(data->entry, " ");
	while (data->entry[i])
	{
		if (data->entry[i] == '|')
			if (check_pipes(data->entry, i) == 0)
				data->nb_pipes++;
		i++;
	}
	return (i);
}