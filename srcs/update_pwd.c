/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 23:32:36 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/29 23:33:01 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_relative_path(t_data *data)
{
	char	*pwd_var;

	pwd_var = get_var("PWD", data);
	if (!pwd_var)
		msh_exit(data);
	if (!ft_strncmp(data->relative_path, pwd_var,
			ft_strlen(data->relative_path))
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
