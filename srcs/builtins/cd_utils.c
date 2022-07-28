/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:18:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/28 14:31:43 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_double_dash(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '-')
		i++;
	if (i == 2 && str[i] == '\0')
		return (2);
	if (i > 2 || (i == 2 && str[i]))
		return (-1);
	return (0);
}

int	is_dash(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = is_double_dash(str);
	while (str[i] && str[i] == '-')
		i++;
	if (i == 1 && str[i] == '\0')
		return (1);
	return (ret);
}

void	swap_paths(t_data *data)
{
	char	*tmp;

	tmp = data->old_path;
	data->old_path = data->relative_path;
	data->relative_path = tmp;
}

int	cd_home(char *path, char *name, t_data *data)
{
	if (!path)
		msh_exit(data);
	if (!ft_strncmp(name, "HOME", ft_strlen("HOME")))
	{
		if (chdir(path) == -1)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		free(data->old_path);
		data->old_path = ft_strdup(data->relative_path);
		free(data->relative_path);
		data->relative_path = ft_strdup(path);
		free(path);
		if (!data->relative_path || !data->old_path)
			msh_exit(data);
		return (1);
	}
	if (!ft_strncmp(name, "OLDPWD", ft_strlen("OLDPWD")))
	{
		if (chdir(path) == -1)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		else
			swap_paths(data);
		free(path);
		return (1);
	}
	return (0);
}

int	cd_dash(char *arg, t_data *data)
{
	int		ret;

	ret = is_dash(arg);
	free(arg);
	if (ret == -1)
	{
		ft_putstr_fd("minishell: --: invalid option\n", 2);
		return (2);
	}
	if (ret == 1)
	{
		ft_printf("%s\n", data->old_path);
		return (cd_home(ft_strdup(data->old_path), "OLDPWD", data));
	}
	if (ret == 2)
		return (cd_home(get_var("HOME", data), "HOME", data));
	return (-1);
}
