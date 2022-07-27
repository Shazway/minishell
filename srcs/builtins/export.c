/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:42 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/27 22:00:30 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---------------------OLD EXPORT--------------*/

int	ft_export(t_data *data, int ac, char **av)
{
	int		i;
	int		j;
	int		len;
	char	*p_eq;
	char	**entry;

	if (ac == 1)
		ft_env(data, ac, av);
	else
	{
		entry = malloc(ac * sizeof(char *));
		if (!entry)
			msh_exit(data);
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
				entry[j] = ft_strdup(av[i]);
				if (!entry[j])
				{
					str_arr_free(entry);
					msh_exit(data);
				}
				j++;
			}
			else if (p_eq)
				ft_printf("minishell: export: `%s': not a valid identifier\n",
					av[i]);
			i++;
		}
		entry[j] = NULL;
		update_env(data, entry, j);
		str_arr_free(entry);
	}
	return (0);
}

void	update_pwd(t_data *data)
{
	free(data->relative_path);
	free(data->old_path);
	data->relative_path = get_var("PWD", data);
	if (!data->relative_path)
		msh_exit(data);
	data->old_path = get_var("OLDPWD", data);
	if (!data->old_path)
		msh_exit(data);
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
