/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:24:29 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/12 22:00:22 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_double_dash(char *str)
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
//----------TO DO BEFORE CD: CHANGE ENVIRONMENT VARIABLE : SWAP $OLDPWD and $PWD//
char	*dash_dir(char *str, int ret)
{
	if (ret == 1)
		return (getenv("OLDPWD"));
	if (ret == 2)
		return (getenv("HOME"));
	return (str);
}

int	is_dash(char	*str)
{
	int	i;
	int ret;

	i = 0;
	ret = is_double_dash(str);
	while (str[i] && str[i] == '-')
		i++;
	if (i == 1 && str[i] == '\0')
		return (1);
	return (ret);
}

int		change_path(char *str, char *path)
{
	if (is_double_dash(str) == -1)
		return (printf("bash: --: invalid option\n"));
	if (!str)
		if (!getenv("HOME"))
			return (printf("bash: cd: HOME not set\n"));
	if (chdir(str) == -1)
		return (printf("cd: %s: No such file or directory\n", str));
	else
		free(path);
	return (1);
}

char	*concat_path(char *s1, char *s2)
{
	char *temp;

	temp = s1;
	s1 = ft_strjoin(s1, "/");
	free(temp);
	if (!s1)
		return (NULL);
	temp = s1;
	s1 = ft_strjoin(s1, s2);
	free(temp);
	if (!s1)
		return (NULL);
	return (s1);
}

int		cd(int ac, char **str)
{
	char	*path;
	char	*temp;

	path = pwd();
	temp = path;
	if (ac > 2)
	{
		free(temp);
		return (printf("bash: cd: too many arguments\n"));
	}
	printf("Path or folder given is [%s]\n", str[0]);
	if (ac == 1)
		return (change_path(getenv("HOME"), temp));
	if (is_dash(str[0]) != 0)
		return (change_path(dash_dir(str[0], is_dash(str[0])), temp));
	if (str[0][0] == '/')
		return (change_path(str[0], temp));
	path = concat_path(path, str[0]);
	printf("Path to go to is [%s]\n", path);
	if (!path)
		return (printf("Allocation for path failed\n"));
	if (change_path(path, path) == -1)
	{
		free(path);
		return (printf("cd: %s: No such file or directory\n", str[0]));
	}
	return (1);
}
