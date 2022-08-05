/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/05 15:48:16 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prompt_string(t_data *data)
{
	char	*tmp;
	char	*cr_dir;
	char	*crf_dollar;

	cr_dir = ft_strrchr(data->relative_path, '/');
	if ((cr_dir && !cr_dir[1]) || !cr_dir)
		cr_dir = data->relative_path;
	else
		cr_dir = cr_dir + 1;
	crf_dollar = ft_strjoin(cr_dir,
			"\001 ▶\002 \001\033[1;34m\002""\001\033[0m\002");
	if (!crf_dollar)
		msh_exit(data, 1);
	tmp = data->prompt;
	data->prompt = ft_strjoin("\001\033[1;32m\002""╔\002"
			"\001\033[1;32m\002"" minishell" " " "\001╝\002" " " "\001\033[1;31m\002""",
			crf_dollar);
	free(crf_dollar);
	free(tmp);
	if (!data->prompt)
		msh_exit(data, 1);
}

int	msh_init(t_data *data, char **env)
{
	data->signals = NULL;
	data->input = NULL;
	data->cmd = NULL;
	data->pips = NULL;
	data->prompt = NULL;
	data->error_msh = NULL;
	data->prompt_path = NULL;
	data->child = -1;
	g_cmd_status = 0;
	data->n_cmd = 0;
	data->env_str = NULL;
	data->relative_path = NULL;
	data->old_path = NULL;
	if (msh_allocate(data, env))
		msh_exit(data, 1);
	data->signals->sa_sigaction = sig_info_main;
	if (signal_intercept(data) == -1)
		return (1);
	return (0);
}

void	ministart(t_data *data)
{
	add_history(data->input);
	if (!is_opened_quotes(data) || !check_input(data))
	{
		g_cmd_status = 2;
		ft_putstr_fd(data->error_msh, 2);
		return ;
	}
	data->input = expand_variables(data, data->input, -1);
	if (!data->input)
		msh_exit(data, 1);
	if (parsing(data))
	{
		delete_quotes(data);
		open_redirections(data);
		search_cmds(data);
		execute(data);
		free_pipes(data);
		ft_lstclear(&data->cmd, &free_cmd);
	}
}

int	only_isspace(char *str)
{
	int	i;

	i = 0;
	if (!ft_strlen(str))
		return (1);
	while (str && str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	minishell_sh(t_data *data)
{
	int	leave;

	leave = 0;
	if (data->input)
		leave = 1;
	while (1)
	{
		set_prompt_string(data);
		if (!leave)
			data->input = readline(data->prompt);
		if (!data->input)
			break ;
		else if (!only_isspace(data->input))
			ministart(data);
		if (leave)
			msh_exit(data, 0);
		data->input = ft_free(data->input);
	}
}
