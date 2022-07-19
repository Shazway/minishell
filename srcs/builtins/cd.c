/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:24:29 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/19 17:12:45 by tmoragli         ###   ########.fr       */
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

int	change_path(char *goal, char *foldername)
{
	if (chdir(goal) == -1)
	{
		printf("cd: %s: No such file or directory\n", foldername);
		free(goal);
		free(foldername);
		return (-1);
	}
	else
	{
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
		return (change_path(arg, arg));
	path = pwd(data);
	path = concat_path(path, arg);
	printf("Path to go to is [%s]\n", path);
	if (!path)
		return (-1);
	if (change_path(path, arg) == -1)
		return (-1);
	return (1);
}
