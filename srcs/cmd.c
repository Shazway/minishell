/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:20:42 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/19 22:29:41 by mdkhissi         ###   ########.fr       */
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
		current_cmd->fullpath = ft_strdup(current_cmd->name);
        current_cmd->builtin = is_builtin(current_cmd->name);
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

int	is_builtin(char *cmd_name)
{
	char	*builtins[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int		i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(builtins[i], cmd_name, ft_strlen(cmd_name)))
			return (1);
		i++;
	}
	return (0);
}

int	nofork_builtin(char *fullpath)
{
	
	if (!ft_strncmp(fullpath, "cd", 2))
		return (1);
	else if (!ft_strncmp(fullpath, "export", 6))
		return (1);
	else if (!ft_strncmp(fullpath, "unset", 5))
		return (1);
	else if (!ft_strncmp(fullpath, "exit", 4))
		return (1);
	else
		return (0);
}