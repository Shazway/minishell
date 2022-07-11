/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/11 16:48:28 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_init(t_data *data)
{
	extern struct sigaction g_signals;

	g_signals.sa_sigaction = sig_info;
	data->read_ret = -1;
	data->buf_trash = NULL;
	data->input = NULL;
	data->output = NULL;
	data->commands = NULL;
	data->env_str = NULL;
	if (set_env(data))
		return (1);
	data->cmd = NULL;
	return (0);
}

int	msh_free(t_data *data)
{
	free(data->buf_trash);
	free(data->input);
	free(data->output);
	str_arr_free(data->commands);
	str_arr_free(data->env_str);
	free(data->cmd);
	free(data);
	return (1);
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
