/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:24:29 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/19 16:32:23 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*----------TO DO BEFORE CD:
CHANGE ENVIRONMENT VARIABLE : SWAP $OLDPWD and $PWD*/
int	change_path(char *goal)
{
	if (chdir(goal) == -1)
	{
		free(goal);
		printf("cd: %s: No such file or directory\n", goal);
		return (-1);
	}
	else
		free(goal);
	return (1);
}

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
		return (change_path(arg));
	path = pwd(data);
	path = concat_path(path, arg);
	free(arg);
	printf("Path to go to is [%s]\n", path);
	if (!path)
		return (-1);
	if (change_path(path) == -1)
		return (-1);
	return (1);
}
