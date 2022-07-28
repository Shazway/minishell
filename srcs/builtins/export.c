/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:42 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/28 20:44:31 by tmoragli         ###   ########.fr       */
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

void	update_relative_path(t_data *data)
{
	char	*pwd_var;

	pwd_var = get_var("PWD", data);
	if (!pwd_var)
		msh_exit(data);
	if (!ft_strncmp(data->relative_path, pwd_var, ft_strlen(data->relative_path))
		|| chdir(pwd_var) == -1)
	{
		free(pwd_var);
		return ;
	}
	else
	{
		free(data->relative_path);
		data->relative_path = ft_strdup(pwd_var);
	}
	free(pwd_var);
	if (!data->relative_path)
		msh_exit(data);
}

void	update_old_path(t_data *data)
{
	char	*old_pwd_var;

	old_pwd_var = get_var("OLDPWD", data);
	if (!old_pwd_var)
		msh_exit(data);
	if (!ft_strncmp(data->old_path, old_pwd_var, ft_strlen(data->old_path))
		|| chdir(old_pwd_var) == -1)
	{
		free(old_pwd_var);
		return ;
	}
	else
	{
		free(data->old_path);
		data->old_path = ft_strdup(old_pwd_var);
	}
	free(old_pwd_var);
	if (!data->old_path)
		msh_exit(data);
}
void	update_pwd(t_data *data)
{
	update_relative_path(data);
	update_old_path(data);
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
