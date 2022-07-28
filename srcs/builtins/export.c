/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:42 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/28 23:41:28 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_data *data, int ac, char **av)
{
	int		len_entry;
	char	**ids;
	char	**entry;

	if (ac == 1)
		return (ft_env(data, ac, av));
	ids = malloc(ac * sizeof(char *));
	if (!ids)
		msh_exit(data);
	entry = malloc(ac * sizeof(char *));
	if (!entry)
		msh_exit(data);
	len_entry = export_worker(ids, entry, ac, av);
	if (len_entry == -1)
		msh_exit(data);
	else if (len_entry == 0)
	{
		free(ids);
		free(entry);
		return (0);
	}
	ids[len_entry] = NULL;
	entry[len_entry] = NULL;
	update_env(data, ids, entry, len_entry);
	return (0);
}

int	export_worker(char **ids, char **entry, int ac, char **av)
{
	int		i;
	int		j;
	char	*p_eq;
	int		len;

	i = 0;
	j = 0;
	while (++i < ac)
	{
		p_eq = ft_strchr(av[i], '=');
		len = (p_eq - &av[i][0]) * (p_eq != 0) + ft_strlen(av[i]) * (!p_eq);
		if (is_validid(av[i], len) && p_eq)
		{
			ids[j] = ft_strndup(av[i], len);
			if (!ids[j])
				return ((!str_arr_free(ids)) * -1);
			entry[j++] = ft_strdup(av[i]);
			if (!entry[j])
				return ((!str_arr_free(entry)) * -1);
		}
		else if (p_eq)
			ft_printf("minishell: export: `%s': not a valid identifier\n",
				av[i]);
	}
	return (j);
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

void	update_env(t_data *data, char **ids, char **entry, int len_entry)
{
	int		i;
	int		k;

	i = -1;
	while (data->env_str[++i])
	{
		k = -1;
		while (entry[++k])
		{
			if (entry[k][0] &&
				ft_strnstr(data->env_str[i], ids[k], 0) == data->env_str[i])
			{
				data->env_str[i] = ft_s_replace(data->env_str[i], ft_strdup(entry[k]));
				entry[k] = ft_str_zero(entry[k]);
				len_entry--;
				break ;
			}
		}
	}
	str_arr_free(ids);
	if (len_entry > 0)
		data->env_str = str_arr_add(data->env_str, i, entry, len_entry);
	else
		str_arr_free(entry);
}

char	*ft_str_zero(char	*str)
{
	free(str);
	return (ft_strdup(""));
}