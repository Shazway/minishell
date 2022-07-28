/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:22:33 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/28 19:11:51 by mdkhissi         ###   ########.fr       */
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
		current_cmd->builtin = is_builtin(data, current_cmd);
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

t_cmd	*init_cmd(int i)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->i = i;
	cmd->ac = 0;
	cmd->to_fork = 1;
	cmd->builtin = 0;
	cmd->fin = -1;
	cmd->fout = -1;
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->fullpath = NULL;
	return (cmd);
}

void	free_cmd(void *vcmd)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)vcmd;
	free(cmd->name);
	str_arr_free(cmd->args);
	free(cmd->fullpath);
	close_cmd_files(cmd);
	free(cmd);
}

void	close_cmd_files(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->fin != -1)
		close(cmd->fin);
	if (cmd->fout != -1)
		close(cmd->fout);
}

void	cmd_notfound(char *cmd_name)
{
	ft_printf("%s: command not found\n", cmd_name);
}
