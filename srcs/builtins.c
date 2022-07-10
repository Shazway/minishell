/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:45:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/10 20:03:36 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(int ac, char **av)
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

int	check_echo_n(char *str)
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
void	shell_exit(int error)
{
	exit(error);
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

void	ft_export(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**new_env;
	char	*eq;
	int		len;
	int		j;

	if (cmd->ac == 1)
		ft_env(data, cmd);
	else
	{
		i = 1;
		while (i < cmd->ac)
		{
			eq = ft_strchr(cmd->args[i], '=');
			if (!eq)
				len = ft_strlen(cmd->args[i]);
			else
				len = eq - cmd->args[i][0];
			j = 0;
			while (j < len)
			{
				if (!(ft_isalnum(cmd->args[i][j]) && cmd->args[i][j] == '_'))
					break ;
				j++;
			}
			ft_strdup(cmd->args[i]);
		}
	}
}