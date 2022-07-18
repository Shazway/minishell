/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:42 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/18 16:49:17 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *data, int ac, char **av)
{
	int		i;
	int		j;
	int		len;
	char	*p_eq;
	char	**entry;

	if (ac == 1)
		ft_env(data, ac);
	else
	{

		printf("ac = %d\n", ac);
		entry = malloc(ac * sizeof(char *));
		entry[ac - 1] = NULL;
		i = 1;
		j = 0;
		while (i < ac)
		{
			p_eq = ft_strchr(av[i], '=');
			if (!p_eq)
				len = ft_strlen(av[i]);
			else
				len = p_eq - &av[i][0];
			if (is_validid(av[i], len) && p_eq)
			{
				entry[j] = av[i];
				j++;
			}
			else if (!is_validid(av[i], len) && p_eq)
				printf("minishell: export: `%s': not a valid identifier\n", av[i]);
			i++;
		}
		update_env(data, entry, j);
		//str_arr_free(entry);
	}
}

int	is_validid(char	*identifier, int len)
{
	int	i;

	i = 0;
	if (len == -1)
	{
		while (identifier[i])
		{
			if (!(ft_isalnum(identifier[i]) || identifier[i] == '_'))
			{
				return (i);
			}
			i++;
		}
	}
	else
	{
		while (i < len && identifier[i])
		{
			if (!(ft_isalnum(identifier[i]) || identifier[i] == '_'))
			{
					return (0);
			}
			i++;
		}
	}
	return (i);
}
