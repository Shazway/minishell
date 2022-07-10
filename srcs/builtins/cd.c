/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:24:29 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/10 20:31:11 by tmoragli         ###   ########.fr       */
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

char	*path_finder(char *str)
{
	return (str);
}

int		directory_exists(char *s)
{
	(void)s;
	return (9);
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
