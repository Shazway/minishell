/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:45:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/04 03:32:53 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_echo_n(char *str)
{
	int i;

	i = 0;
	if (str[i] != '-')
		return (1);
	while (str && str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	echo(int ac, char **av)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 0;
	if (ac == 1)
		return(write(1, "\n", 1));
	while (av && av[i])
	{
		if (check_echo_n(av[i]))
			ft_putstr_fd(av[i], 1);
		else
			new_line = 0;
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}

char	*pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	return (path);
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
