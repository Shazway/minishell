/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:24:29 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/08/04 15:40:23 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_path(char *goal, char *folder_name)
{
	char	*temp;

	if (!goal)
		return (NULL);
	if (ft_strncmp(goal, "/", ft_strlen(goal)))
	{
		temp = goal;
		goal = ft_strjoin(goal, "/");
		free(temp);
	}
	if (!goal)
		return (NULL);
	temp = goal;
	goal = ft_strjoin(goal, folder_name);
	free(temp);
	if (!goal)
		return (NULL);
	return (goal);
}

int	export_paths(t_data *data)
{
	char	**arg;

	arg = malloc(4 * sizeof(char *));
	if (!arg)
		msh_exit(data, 1);
	arg[3] = NULL;
	arg[0] = ft_strdup("export");
	arg[1] = ft_strjoin("PWD=", data->relative_path);
	arg[2] = ft_strjoin("OLDPWD=", data->old_path);
	if (!arg[0] || !arg[1] || !arg[2])
		return (str_arr_free(arg) != NULL);
	ft_export(data, 3, arg);
	str_arr_free(arg);
	return (1);
}

int	change_path_worker(char *goal, char *foldername, t_data *data)
{
	free(data->old_path);
	data->old_path = ft_strdup(data->relative_path);
	ft_free_strs(&goal, &foldername, NULL, NULL);
	if (!data->old_path)
		msh_exit(data, 1);
	free(data->relative_path);
	data->relative_path = getcwd(NULL, 0);
	if (!data->relative_path)
		msh_exit(data, 1);
	if (!export_paths(data))
		return (0);
	return (1);
}

int	change_path(char *goal, char *foldername, t_data *data)
{
	if (!foldername || !goal)
	{
		ft_free_strs(&foldername, &goal, NULL, NULL);
		msh_exit(data, 1);
	}
	if (chdir(goal) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(foldername);
		ft_free_strs(&goal, &foldername, NULL, NULL);
		return (1);
	}
	if (!change_path_worker(goal, foldername, data))
		msh_exit(data, 1);
	return (0);
}

int	cd(t_data *data, int ac, char **str)
{
	char	*path;
	char	*arg;

	arg = NULL;
	if (ac > 2)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2) > 0);
	if (ac == 1 || (ac == 2 && !ft_strncmp(str[1], "~", ft_strlen(str[1]))))
		return (cd_home(get_var("HOME", data, 0), "HOME", data));
	arg = ft_strdup(str[1]);
	if (!arg)
		msh_exit(data, 1);
	if (is_dash(arg) != 0)
		return (cd_dash(arg, data));
	if (arg[0] == '/')
		return (change_path(arg, ft_strdup(arg), data));
	path = ft_strdup(data->relative_path);
	path = concat_path(path, arg);
	if (!path)
		msh_perexit(data, NULL, arg);
	if (change_path(path, arg, data))
		return (1);
	return (0);
}
