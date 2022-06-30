/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:59:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/30 21:20:39 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	count_words(t_data *data)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (data->entry[i])
	{
		while (data->entry[i] && ft_isblank(data->entry[i]))
			i++;
		if (data->entry[i] != '\0')
			count++;
		while (data->entry[i] && !ft_isblank(data->entry[i]))
			i++;
	}
	return (count);
}

int	parsing(t_data *data)
{
	int	pipe_i;
	int	count;
	int i;

	i = 0;
	pipe_i = 0;
	data->entry = ft_strtrim(data->entry, " ");
	while (count_words(data))
		data->size_cmd++;
	
	while (data->entry[pipe_i] && data->entry[pipe_i] != '|')
		i++;
	if (data->entry[pipe_i + 1] && data->entry[pipe_i] == '|')
		i++;
	return (i);
}