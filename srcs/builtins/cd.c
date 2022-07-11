/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:24:29 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/11 17:32:38 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_double_dot(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '.')
		i++;
	if (i == 2 && str[i] == '\0')
		return (1);
	return (0);
}

char	*previous_dir(char *str)
{
	int		i;

	i = 0;
	while(str[i])
		i++;
	i--;
	while(str[i] != '/' && i != 0)
	{
		str[i] = 0;
		i--;
	}
	return (str);
}

int		change_path(char *str, char *path)
{
	if (!str)
	{
		if (!getenv("HOME"))
			return (printf("bash: cd: HOME not set\n"));
	}
	if (chdir(str) == -1)
		return (-1);
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
	char *path;
	char *temp;

	path = pwd();
	temp = path;
	if (ac > 2)
	{
		free(temp);
		return (printf("bash: cd: too many arguments\n"));
	}
	if (ac == 1)
		return (change_path(getenv("HOME"), temp));
	printf("Folder to go to is [%s]\n", str[0]);
	if (is_double_dot(str[0]))
		return (change_path(previous_dir(path), temp));
	path = concat_path(path, str[0]);
	if (!path)
		return (printf("allocation for path failed\n"));
	if (change_path(path, path) == -1)
	{
		free(path);
		return (printf("cd: %s: no such file or directory\n", str[0]));
	}
}