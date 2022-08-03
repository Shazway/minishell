/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:09:04 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/08/03 22:55:38 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_display(char **envr)
{
	int	i;
	int	len_id;

	i = 0;
	if (!envr)
		return (0);
	while (envr[i])
	{
		len_id = get_id_len(envr[i]);
		printf("declare -x %.*s", len_id + 1, envr[i]);
		printf("\"%s\"\n", envr[i] + len_id + 1);
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
