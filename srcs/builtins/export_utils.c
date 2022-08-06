/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:09:04 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/08/06 14:43:02 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_display(char **envr)
{
	int	i;
	int	len_id;
	int	*in_order;
	int	len;
	int	j;
	int	tmp;

	if (!envr)
		return (0);
	len = str_arr_size(envr);
	in_order = malloc(len * sizeof(int));
	i = 0;
	while (i < len)
	{
		in_order[i] = i;
		i++;
	}
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(envr[in_order[i]], envr[in_order[j]], -1) > 0)
			{
				tmp = in_order[i];
				in_order[i] = in_order[j];
				in_order[j] = tmp;	
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < len)
	{
		len_id = get_id_len(envr[in_order[i]]);
		printf("declare -x %.*s", len_id + 1, envr[in_order[i]]);
		printf("\"%s\"\n", envr[in_order[i]] + len_id + 1);
		i++;
	}
	return (0);
}

char	*id_exist(char **av, int ac, int idx, int len)
{
	int	i;

	i = ac - 1;
	while (av && av[i] && i > idx)
	{
		if (!ft_strncmp(av[i], av[idx], len))
			return (av[i]);
		i--;
	}
	return (NULL);
}

int	is_validid(char	*identifier, int len)
{
	int	i;

	if (ft_isdigit(identifier[0]))
		return (0);
	i = 0;
	while ((i < len || len == -1) && identifier[i])
	{
		if (!(ft_isalnum(identifier[i]) || identifier[i] == '_'))
			return (0);
		i++;
	}
	return (i);
}
