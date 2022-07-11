/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:55:18 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/11 15:27:25 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_arr_free(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	str_arr_size(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}

char	**str_arr_add(char **sarr, char **entry, int len_entry)
{
	int		len_sarr;
	char	**new;
	int		i;
	int		j;

	len_sarr = str_arr_size(sarr);
	new = malloc(sizeof(char *) * (len_sarr + len_entry + 1));
	if (!new)
		return (NULL);
	new[len_sarr + len_entry] = NULL;
	i = 0;
	while (i < len_sarr)
	{
		new[i] = ft_strdup(sarr[i]);
		i++;
	}
	j = 0;
	while (entry && j < len_entry)
	{
		new[i] = ft_strdup(entry[j]);
		j++;
		i++;
	}
	return (new);
}

int	ft_malloc(void **p, int length)
{
	*p = malloc(length);
	if (*p)
		return (1);
	return (0);
}
