/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:24:29 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/19 15:28:08 by tmoragli         ###   ########.fr       */
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

/*----------TO DO BEFORE CD:
CHANGE ENVIRONMENT VARIABLE : SWAP $OLDPWD and $PWD*/
char	*dash_dir(char *str, int ret, t_data *data)
{
	if (ret == 1)
	{
		return (get_var("OLDPWD", data));
	}
	if (ret == 2)
		return (get_var("HOME", data));
	return (str);
}

int	is_dash(char	*str)
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

/*--CHANGE TO **env--*/
int	cd_home(char *path, char *name)
{
	if (!ft_strncmp(name, "HOME", ft_strlen("HOME")))
	{
		if (chdir(path) == -1)
			printf("minishell: cd: HOME not set\n");
		free(path);
		return (1);
	}
	if (!ft_strncmp(name, "OLDPWD", ft_strlen("OLDPWD")))
	{
		if (chdir(path) == -1)
			printf("minishell: cd: OLDPWD not set\n");
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
		printf("minishell: --: invalid option\n");
	if (ret == 1)
		return (cd_home(get_var("OLDPWD", data), "OLDPWD"));
	if (ret == 2)
		return (cd_home(get_var("OLDPWD", data), "OLDPWD"));
	return (-1);
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
		return (change_path(arg, data));
	//FOLDER NAME DIRECTLY//
	path = pwd(data);
	path = concat_path(path, arg);
	free(arg);
	printf("Path to go to is [%s]\n", path);
	if (!path)
		return (-1);
	if (change_path(path, data) == -1)
		return (-1);
	return (1);
}
