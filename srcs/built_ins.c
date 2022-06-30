/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:45:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/30 16:55:18 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*echo(char *str)
{
	int i;

	i = 0;
	while (str && str[i] && str[i] != '|')
	{
		write(1, &str[i], 1);
		i++;
	}
}

char	*pwd(void)
{
	char *path;

	buf = getcwd(NULL, 0);
	return (path)
}

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

int		cd(char *str)
{
	char *path;

	path = pwd();
	if (!str)
		return (chdir(getenv("HOME")));
	if (is_double_dot(str))
		return (chdir(previous_dir(path)));
	if (directory_exists(str))
		return (chdir(path_finder(path)));
	else
		return (printf("cd: no such file or directory : %s\n", str));
}