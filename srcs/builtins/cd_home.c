/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 23:41:15 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/02 16:46:41 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_home(char *path, t_data *data)
{
	if (chdir(path) == -1)
	{
		free(path);
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	free(data->old_path);
	data->old_path = ft_strdup(data->relative_path);
	free(data->relative_path);
	data->relative_path = getcwd(NULL, 0);
	if (!data->relative_path || !data->old_path)
		msh_exit(data, 1);
	return (0);
}

int	to_old(char *path, t_data *data)
{
	if (chdir(path) == -1)
	{
		free(path);
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	swap_paths(data);
	return (0);
}

int	cd_home(char *path, char *name, t_data *data)
{
	if (!path)
		msh_exit(data, 1);
	if (!ft_strncmp(name, "HOME", ft_strlen("HOME")))
		if (to_home(path, data))
			return (1);
	if (!ft_strncmp(name, "OLDPWD", ft_strlen("OLDPWD")))
		if (to_old(path, data))
			return (1);
	free(path);
	return (0);
}
