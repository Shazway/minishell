/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:14:09 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/28 23:53:12 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_arr_size(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}

void	str_arr_display(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
}

char	**str_arr_add(char **sarr, int len_sarr, char **entry, int len_entry)
{
	char	**new;
	int		i;
	int		j;

	if (!ft_sar_alloc(&new, len_sarr + len_entry, sizeof(char *)))
		return (ft_free_sars(&entry, &sarr, NULL, NULL));
	i = -1;
	while (++i < len_sarr)
	{
		new[i] = ft_strdup(sarr[i]);
		if (!new[i])
			return (ft_free_sars(&entry, &sarr, &new, NULL));
	}
	j = -1;
	while (entry && entry[++j])
	{
		if (entry[j][0])
		{
			new[i] = ft_strdup(entry[j]);
			if (!new[i++])
				return (ft_free_sars(&entry, &sarr, &new, NULL));
		}
	}
	ft_free_sars(&entry, &sarr, NULL, NULL);
	return (new);
}

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
	str_arr_free(entry);
	return (new);
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
	to_del = malloc((len_sarr + 1) * sizeof(int));
	if (!to_del)
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
	to_del[j] = -1;
	*len_new = len_sarr - j;
	return (to_del);
}

int	ft_sar_alloc(char ***sarr, size_t len, size_t v_type)
{
	*sarr = malloc((len + 1) * v_type);
	if (!*sarr)
		return (0);
	(*sarr)[len] = NULL;
	return (1);
}
