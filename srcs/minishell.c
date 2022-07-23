/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/24 00:10:46 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_free(t_data *data)
{
	free(data->input);
	free(data->relative_path);
	free(data->old_path);
	str_arr_free(data->env_str);
	ft_lstclear(&data->cmd, &free_cmd);
	free_pipes(data);
	free(data->prompt);
	free(data);
	return (1);
}

void	msh_exit(t_data *data)
{
	perror("minishell: ");
	msh_free(data);
	exit(EXIT_FAILURE);
}

void	alloc_pipes(t_data *data)
{
	data->pips = malloc((data->n_cmd - 1) * sizeof(t_pipex));
	if (!data->pips)
		msh_exit(data);
}

void	init_pipe(t_data *data, int i)
{
	if (pipe(data->pips[i].fd) == (-1))
		msh_exit(data);
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

void	set_prompt_string(t_data *data)
{
	char	*tmp;
	char	*current_folder;
	char	*crf_dolar;

	current_folder = NULL;
	crf_dolar = NULL;
	tmp = NULL;
	current_folder = ft_strrchr(data->relative_path, '/');
	crf_dolar = ft_strjoin(current_folder + 1, "\001 ▶\002 \001\033[1;34m\002""\001\033[0m\002");
	tmp = data->prompt;
	data->prompt = ft_strjoin("\001\033[1;32m\002""╔\002"
				"\001\033[1;32m\002"" minishell" " " "\001╝\002" " " "\001\033[1;31m\002"""
				, crf_dolar);
	free(crf_dolar);
	free(tmp);
}

void	prompt_loop(t_data *data)
{
	while (1)
	{
		if (signal_intercept())
			exit(1);
		set_prompt_string(data);
		data->input = readline(data->prompt);
		if (!data->input)
			break ;
		else
		{
			printf("Input is :%s\n---------\n", data->input);
			add_history(data->input);
			if (!is_opened_quotes(data->input))
			{
				printf("Unclosed quote, try closing the \" or \'\n");
				free(data->input);
				continue ;
			}
			if (ft_strchr(data->input, '$'))
				data->input = expand_variables(data, data->input);
			if (parsing(data))
			{
				open_redirections(data);
				delete_quotes(data);
				search_cmds(data);
				execute(data);
				ft_lstclear(&data->cmd, &free_cmd);
				free_pipes(data);
			}
		}
		free(data->input);
	}
}
