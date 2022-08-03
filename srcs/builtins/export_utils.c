/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:09:04 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/08/02 18:10:12 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_display(char **envr)
{
	int	i;

	i = 0;
	if (!envr)
		return (1);
	while (envr[i])
	{
		ft_printf("declare -x %s\n", envr[i]);
		i++;
	}
	return (0);
}

char	*export_error(char *entry, int *ac)
{
	ft_printf("minishell: export: `%s': not a valid identifier\n", entry);
	*ac -= 1;
	return (ft_str_zero(entry));
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

	i = 0;
	while ((i < len || len == -1) && identifier[i])
	{
		if (!(ft_isalnum(identifier[i]) || identifier[i] == '_'))
			return (0);
		i++;
	}
	return (i);
}

char	*ft_str_zero(char	*str)
{
	free(str);
	return (ft_strdup(""));
}