/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:24:29 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/20 17:25:02 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*----------TO DO BEFORE CD:
CHANGE ENVIRONMENT VARIABLE : SWAP $OLDPWD and $PWD*/

char	*concat_path(char *goal, char *folder_name)
{
	char	*temp;

	temp = goal;
	goal = ft_strjoin(goal, "/");
	free(temp);
	if (!goal)
		return (NULL);
	temp = goal;
	goal = ft_strjoin(goal, folder_name);
	free(temp);
	if (!goal)
		return (NULL);
	return (goal);
}
/*
char	*previous_folder(char *path)
{
	int		i;
	char	*path;

	i = 0;
	while (path && path[i])
		i++;
	while (i > 0 && path[i] != '/')
		i--;
	if (i == 0)
		return (ft_strdup("/"));
	path = ft_substr(path, 0, i);
	i = 0;
	while (path && path[i])
		i++;
	if (!path[i] && path[i - 1] == '/')
	{
		
	}
	return (path);
}

char	*new_pwd(char	*next_pwd, t_data *data)
{
	char	*path;
	char	*folder;
	char	*tmp;

	path = ft_strdup(data->relative_path);
	folder = ft_substr(next_pwd, 0, ft_strchr('/'));
	if (!folder)
	{
		if (path)
		{
			free(path);
			return (concat_path(path, next_pwd));
		}
		return (NULL);
	}
	if (!ft_strncmp(folder, "..", 3))
	{
		tmp = path;
		path = previous_folder(path);
		free(temp);
	}
}
*/
int	change_path(char *goal, char *foldername, t_data *data)
{
	char	*exp[2];

	exp[1] = NULL;
	exp[0] = goal;
	if (chdir(goal) == -1)
	{
		printf("cd: %s: No such file or directory\n", foldername);
		free(goal);
		free(foldername);
		return (-1);
	}
	else
	{
		printf("Path has been changed to : \n");
		str_arr_display(exp);
		ft_export(data, 2, exp);
		free(foldername);
		free(goal);
	}
	return (1);
}

int	cd(int ac, char **str, t_data *data)
{
	char	*path;
	char	*arg;

	if (ac > 2)
		return (printf("minishell: cd: too many arguments\n"));
	if (ac == 1)
		return (cd_home(get_var("HOME", data), "HOME"));
	printf("Path or folder given is [%s]\n", str[0]);
	arg = ft_strdup(str[0]);
	if (is_dash(arg) != 0)
		return (cd_dash(arg, data));
	if (arg[0] == '/')
		return (change_path(arg, arg, data));
	path = data->relative_path;
	path = concat_path(path, arg);
	printf("Path to go to is [%s]\n", path);
	if (!path)
		return (-1);
	if (change_path(path, arg, data) == -1)
		return (-1);
	return (1);
}
