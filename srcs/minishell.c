/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/15 16:52:39 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_free(t_data *data)
{
	free(data->buf_trash);
	free(data->input);
	free(data->output);
	str_arr_free(data->commands);
	str_arr_free(data->env_str);
	ft_lstclear(&data->cmd, &free_cmd);
	free_pips(data->pips, data->n_cmd);
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
	free(cmd->fin);
	free(cmd->fout);
}

void	prompt_loop(t_data *data)
{
	while (1)
	{
		if (signal_intercept())
			exit(1);
		data->input = readline("\033[1;32m""➜ ""\033[1;36m"" minishell ""\033[0m");
		if (!data->input)
			break ;
		if (!(data->input[0] == 0))
		{
			printf("%s\n", data->input);
			add_history(data->input);
			parsing(data);
		}
		free(data->input);
	}
}
