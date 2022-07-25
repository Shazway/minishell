/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:20:42 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/25 23:35:42 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_cmds(t_data *data)
{
	t_list	*cmd_idx;
	t_cmd	*current_cmd;
	char	*fullpath;

	cmd_idx = data->cmd;
	while (cmd_idx != NULL)
	{
		current_cmd = cmd_idx->content;
		current_cmd->builtin = is_builtin(current_cmd);
		if (!current_cmd->builtin)
		{
			fullpath = get_path(current_cmd->name, data->env_str);
			if (fullpath)
			{
				free(current_cmd->fullpath);
				current_cmd->fullpath = fullpath;
			}
		}
		cmd_idx = cmd_idx->next;
	}
}

int	is_builtin(t_cmd *cmd)
{
	char		*builtins[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	const FP	farr[7]= {&ft_echo, &cd, &pwd, &ft_export, &ft_unset, &ft_env, &shell_exit};
	int		i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(builtins[i], cmd->name, ft_strlen(cmd->name)))
		{
			cmd->builtin = 1;
			cmd->func = farr[i];
			if (i == 1 || i == 3 || i == 4 || i == 6)
				cmd->no_fork = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int		is_path(char *s)
{
	(void)s;
	return (0);
}

char	*get_path(char *c_name, char **envr)
{
	int		i;
	char	*path_var;
	char	**path_array;
	char	*working_cmd;

	if (ft_strchr(c_name, '/'))
	{
		path_var = ft_strdup(c_name);
		return (path_var);
	}
	i = 0;
	if (envr[0])
	{
		while (envr[i] != NULL)
		{
			path_var = ft_strnstr(envr[i], "PATH=", 5);
			if (path_var != NULL)
				break ;
			i++;
		}
		if (!path_var)
			return (NULL);
		path_var += 5;
		path_array = ft_split(path_var, ':');
		working_cmd = parse_path(path_array, c_name);
		str_arr_free(path_array);
		if (working_cmd)
			return (working_cmd);
	}
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