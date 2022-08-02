/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:14:09 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/08/01 20:53:09 by mdkhissi         ###   ########.fr       */
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
		return (ft_free_sars(NULL, &sarr, NULL, NULL));
	i = -1;
	while (++i < len_sarr)
	{
		new[i] = ft_strdup(sarr[i]);
		if (!new[i])
			return (ft_free_sars(NULL, &sarr, &new, NULL));
	}
	j = -1;
	while (entry && entry[++j])
	{
		if (entry[j][0])
		{
			new[i] = ft_strdup(entry[j]);
			if (!new[i++])
				return (ft_free_sars(NULL, &sarr, &new, NULL));
		}
	}
	ft_free_sars(NULL, &sarr, NULL, NULL);
	return (new);
}

int	ft_sar_alloc(char ***sarr, size_t len, size_t v_type)
{
	*sarr = malloc((len + 1) * v_type);
	if (!*sarr)
		return (0);
	(*sarr)[len] = NULL;
	return (1);
}
