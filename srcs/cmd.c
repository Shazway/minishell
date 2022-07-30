/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:20:42 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/30 21:33:03 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_data *data, t_cmd *cmd)
{
	const char	*b[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	const t_fp	f[7] = {&ft_echo, &cd, &pwd, &ft_export,
		&ft_unset, &ft_env, &shell_exit};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (cmd->name && !ft_strncmp(cmd->name, b[i], -1))
		{
			cmd->builtin = 1;
			cmd->func = f[i];
			if ((i == 1 || i == 3 || i == 4 || i == 6)
				&& ft_lstsize(data->cmd) == 1)
				cmd->to_fork = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_path(char *c_name, char **envr)
{
	int		i;
	char	*path_var;
	char	**path_array;
	char	*working_cmd;

	if (ft_strchr(c_name, '/'))
		return (ft_strdup(c_name));
	if (!envr)
		return (NULL);
	i = -1;
	while (envr[++i] != NULL)
	{
		path_var = ft_strnstr(envr[i], "PATH=", 5);
		if (path_var)
			break ;
	}
	if (!path_var)
		return (NULL);
	path_var += 5;
	path_array = ft_split(path_var, ':');
	working_cmd = parse_path(path_array, c_name);
	str_arr_free(path_array);
	if (working_cmd)
		return (working_cmd);
	return (NULL);
}

char	*parse_path(char **path_array, char *c_name)
{
	int		i;
	char	*working_cmd;
	char	*slashcmd;
	int		found;

	slashcmd = ft_strjoin("/", c_name);
	found = 0;
	i = 0;
	while (!found && path_array && path_array[i] != NULL)
	{
		working_cmd = ft_strjoin(path_array[i++], slashcmd);
		if (access(working_cmd, F_OK) == 0)
			found = 1;
		if (!found)
			free(working_cmd);
	}
	free(slashcmd);
	if (found)
		return (working_cmd);
	else
		return (NULL);
}

void	exec_builtin(t_data *data, t_cmd *cmd)
{
	g_cmd_status = cmd->func(data, cmd->ac, cmd->args);
	if (cmd->to_fork || !ft_strncmp(cmd->name, "exit", 4))
	{
		if (!ft_strncmp(cmd->name, "exit", 4))
		{
			if (g_cmd_status == 2 && !cmd->to_fork)
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd->args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
			}
			else if (g_cmd_status != 257 && !cmd->to_fork)
				ft_putstr_fd("exit\n", 2);
			else if (g_cmd_status == 257)
				g_cmd_status = 1;
		}
		msh_free(data);
		exit(g_cmd_status);
	}
}
