/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/20 17:19:11 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_free(t_data *data)
{
	free(data->input);
	str_arr_free(data->env_str);
	ft_lstclear(&data->cmd, &free_cmd);
	free_pipes(data);
	free(data);
	return (1);
}

void	msh_exit(t_data *data)
{
	perror("minishell: ");
	msh_free(data);
	exit(EXIT_FAILURE);
}

void	free_pipes(t_data *data)
{
	close_pipes(data->pips, data->n_cmd - 1);
	free(data->pips);
	data->pips = NULL;
}

void	close_pipes(t_pipex *pips, int n)
{
	int	i;

	if (!pips)
		return ;
	i = 0;
	while (i < n)
	{
		if (pips[i].fd[0] != -1)
			close(pips[i].fd[0]);
		if (pips[i].fd[1] != -1)
			close(pips[i].fd[1]);
		i++;
	}
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

void	prompt_loop(t_data *data)
{
	while (1)
	{
		if (signal_intercept())
			exit(1);
		data->input = readline("\001\033[1;36m\002""\001➜\002 "
				"\001\033[1;32m\002"" minishell ""\001\033[0m\002");
		if (!data->input)
			break ;
		else
		{
			printf("Input is :%s\n---------\n", data->input);
			add_history(data->input);
			if (parsing(data))
			{
				open_redirections(data);
				expand_variables(data);
				search_cmds(data);
				execute(data);
				ft_lstclear(&data->cmd, &free_cmd);
				free_pipes(data);
			}
		}
		free(data->input);
	}
}
