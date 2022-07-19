/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/20 01:26:53 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_free(t_data *data)
{
	free(data->input);
	str_arr_free(data->env_str);
	free(data);
	return (1);
}

void	free_pips(t_pipex *pips, int n)
{
	int	i;

	if (!pips)
		return ;
	i = 0;
	while (i < n - 1)
	{
		close(pips[i].fd[0]);
		close(pips[i].fd[1]);
		i++;
	}
	free(pips);
}

void	free_cmd(void *vcmd)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)vcmd;
	free(cmd->name);
	str_arr_free(cmd->args);
	free(cmd->fullpath);
	if (cmd->fin != -1)
		close(cmd->fin);
	if (cmd->fout != -1)
		close(cmd->fout);
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
				print_fullpath(data);
				execute(data);
				ft_lstclear(&data->cmd, &free_cmd);
				free_pips(data->pips, data->n_cmd);
			}
		}
		free(data->input);
	}
}
