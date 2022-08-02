/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_del_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:18:47 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/01 20:52:22 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**str_arr_del(char **sarr, char **entry, int len_entry)
{
	char	**new;
	int		i;
	int		j;
	int		*to_del;
	int		len_new;

	to_del = sarrdel_worker(sarr, entry, len_entry, &len_new);
	new = malloc((len_new + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	new[len_new] = NULL;
	i = 0;
	j = 0;
	while (i - j < len_new)
	{
		if (i == to_del[j])
			j++;
		else
			new[i - j] = ft_strdup(sarr[i]);
		i++;
	}
	free(to_del);
	str_arr_free(sarr);
	return (new);
}

int	*end_sarrdel_worker(int *to_del, int **len_new, int len_sarr, int j)
{
	to_del[j] = -1;
	**len_new = len_sarr - j;
	return (to_del);
}

int	*sarrdel_worker(char **sarr, char **entry, int len_entry, int *len_new)
{
	int		i;
	int		j;
	int		k;
	int		len_sarr;
	int		*to_del;

	len_sarr = str_arr_size(sarr);
	i = -1;
	j = 0;
	if (!ft_malloc((void **)(&to_del), (len_sarr + 1) * sizeof(int)))
		return (NULL);
	while (sarr[++i])
	{
		k = -1;
		while (++k < len_entry)
		{
			if (ft_strnstr(sarr[i], entry[k], 0) == sarr[i])
			{
				to_del[j] = i;
				j++;
				break ;
			}
		}
	}
	return (end_sarrdel_worker(to_del, &len_new, len_sarr, j));
}
