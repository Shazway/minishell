/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 20:50:18 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/01 03:12:19 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_quote_fill(char *str, char *new, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < size)
	{
		if (str[i] != '\'' && str[i] != '"')
			new[j++] = str[i];
		i++;
	}
	free(str);
	return (new);
}

char	*del_quote(char *str)
{
	char	*new;
	int		i;
	int		size;

	size = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str && str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			size++;
		i++;
	}
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = '\0';
	return (del_quote_fill(str, new, size));
}
