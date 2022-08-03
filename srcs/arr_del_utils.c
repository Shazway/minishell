/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_del_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:18:47 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/03 16:13:57 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**str_arr_del(char **sarr, char **entry, int len_entry)
{
	char	**new;
	int		*to_del;
	int		len_new;

	to_del = sarrdel_worker(sarr, entry, len_entry, &len_new);
	new = malloc((len_new + 1) * sizeof(char *));
	if (!new || !to_del)
	{
		free(new);
		return (ft_free(to_del));
	}
	new[len_new] = NULL;
	new = new_env(len_new, sarr, new, to_del);
	free(to_del);
	str_arr_free(sarr);
	return (new);
}

char	**new_env(int len_new, char **sarr, char **new, int *to_del)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i - j < len_new)
	{
		if (i == to_del[j])
			j++;
		else
		{
			new[i - j] = ft_strdup(sarr[i]);
			if (!new[i - j])
			{
				free(to_del);
				str_arr_free(sarr);
				return (str_arr_free(new));
			}
		}
		i++;
	}
	return (new);
}

int	find_to_del(int	*to_del, int len_entry, char **sarr, char **entry)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
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
	return (j);
}

int	*sarrdel_worker(char **sarr, char **entry, int len_entry, int *len_new)
{
	int		j;
	int		len_sarr;
	int		*to_del;

	len_sarr = str_arr_size(sarr);
	if (!ft_malloc((void **)(&to_del), (len_sarr + 1) * sizeof(int)))
		return (NULL);
	if (!to_del)
		return (NULL);
	j = find_to_del(to_del, len_entry, sarr, entry);
	to_del[j] = -1;
	*len_new = len_sarr - j;
	return (to_del);
}
