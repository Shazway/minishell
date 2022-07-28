/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:19:28 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/28 02:03:43 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_free(t_data *data)
{
	rl_clear_history();
	free(data->input);
	free(data->prompt);
	free(data->relative_path);
	free(data->old_path);
	ft_lstclear	(&data->cmd, &free_cmd);
	free_pipes(data);
	str_arr_free(data->env_str);
	free(data);
	return (1);
}

void	msh_exit(t_data *data)
{
	msh_free(data);
	exit(EXIT_FAILURE);
}

int	msh_init(t_data *data)
{
	g_signals.sa_sigaction = sig_info_main;
	data->input = NULL;
	data->env_str = NULL;
	data->cmd = NULL;
	data->n_cmd = 0;
	data->pips = NULL;
	data->ret = 0;
	data->prompt = NULL;
	data->error_msh = "";
	data->relative_path = NULL;
	data->old_path = NULL;
	if (!set_env(data))
		return (1);
	data->relative_path = get_var("PWD", data);
	if (!data->relative_path)
		return (1);
	data->old_path = ft_strdup(data->relative_path);
	if (!data->old_path)
		return (1);
	return (0);
}
