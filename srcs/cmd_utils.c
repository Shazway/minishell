/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:22:33 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/04 15:50:59 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_cmds(t_data *data)
{
	t_list	*i;
	t_cmd	*cmd;
	char	*fullpath;

	i = data->cmd;
	while (i != NULL)
	{
		cmd = i->content;
		if (!cmd->name[0])
		{
			i = i->next;
			continue ;
		}
		cmd->builtin = is_builtin(data, cmd);
		if (!cmd->builtin)
		{
			fullpath = get_path(cmd->name, data->env_str, data);
			if (!fullpath)
				msh_exit(data, 1);
			free(cmd->fullpath);
			cmd->fullpath = fullpath;
		}
		i = i->next;
	}
}

t_cmd	*init_cmd(int i)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->i = i;
	cmd->redirect_success = 1;
	cmd->ac = 0;
	cmd->to_fork = 1;
	cmd->builtin = 0;
	cmd->fin = -1;
	cmd->fout = -1;
	cmd->name = ft_strdup("\0");
	if (!cmd->name)
		return (ft_free(cmd));
	cmd->args = NULL;
	cmd->fullpath = ft_strdup("\0");
	if (!cmd->fullpath)
	{
		free(cmd->name);
		free(cmd);
		return (NULL);
	}
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_cmd_status = 127;
}
