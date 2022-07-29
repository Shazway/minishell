/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:19:28 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/29 18:20:52 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_free(t_data *data)
{
	rl_clear_history();
	free(data->signals_test);
	free(data->input);
	free(data->prompt);
	free(data->relative_path);
	free(data->old_path);
	free(data->prompt_path);
	ft_lstclear(&data->cmd, &free_cmd);
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

void	msh_perexit(t_data *data, char *scall)
{
	ft_putstr_fd("minishell: ", 2);
	perror(scall);
	msh_free(data);
	exit(EXIT_FAILURE);
}

void	msh_persignal(char *scall, int sigvalue)
{
	ft_putstr_fd("minishell: ", 2);
	perror(scall);
	g_cmd_status = sigvalue;
}

int	msh_init(t_data *data)
{
	data->signals_test = malloc(sizeof(struct sigaction));
	memset(data->signals_test, 0, sizeof(struct sigaction));
	data->signals_test->sa_sigaction = sig_info_main;
	data->input = NULL;
	data->env_str = NULL;
	data->cmd = NULL;
	data->pips = NULL;
	data->prompt = NULL;
	data->error_msh = NULL;
	data->relative_path = NULL;
	data->old_path = NULL;
	data->prompt_path = NULL;
	data->child = -1;
	g_cmd_status = 0;
	data->n_cmd = 0;
	if (!set_env(data))
		return (1);
	data->relative_path = get_var("PWD", data);
	data->old_path = ft_strdup(data->relative_path);
	if (!data->relative_path || !data->old_path)
		return (1);
	return (0);
}
