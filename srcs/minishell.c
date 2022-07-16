/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/16 22:36:39 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_free(t_data *data)
{
	free(data->buf_trash);
	free(data->input);
	free(data->output);
	str_arr_free(data->env_str);
	//free_pips(data->pips, data->n_cmd);
	return (1);
}

void	free_pips(t_pipex *pips, int n)
{
	int	i;

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
	t_cmd *cmd;

	cmd = (t_cmd *)vcmd;
	free(cmd->cmd);
	str_arr_free(cmd->args);
	free(cmd->fullpath);
	free(cmd);
}

/*
void	ft_open_files(t_data *data)
{
	t_cmd	*cmd;
	t_list	*c_idx;
	int		i;

	c_idx = data->cmd;
	while (c_idx != NULL)
	{
		cmd = c_idx->content;
		i = 0;
		while (cmd->args[i])
		{
			if (!ft_strncmp(cmd->args[i], "<", 1))
			{
				cmd->fin
			}
			i++;
		}
		c_idx = c_idx->next;
	}	
}
*/
void	prompt_loop(t_data *data)
{
	while (1)
	{
		if (signal_intercept())
			exit(1);
		data->input = readline("\033[1;32m""➜ ""\033[1;36m"" minishell ""\033[0m");
		if (!data->input)
			break ;
		else if (!(data->input[0] == 0))
		{
			printf("Input is :%s\n---------\n", data->input);
			add_history(data->input);
			parsing(data);
			open_redirections(data);
			search_cmds(data);
			execute(data);
		}
		free(data->input);
	}
}
