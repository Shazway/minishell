/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:19:28 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/02 00:58:31 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_free(t_data *data)
{
	rl_clear_history();
	free(data->signals);
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

void	msh_exit(t_data *data, int bad_malloc)
{
	if (bad_malloc)
		g_cmd_status = 12;
	msh_free(data);
	exit(g_cmd_status);
}

void	msh_perexit(t_data *data, char *scall, void *p)
{
	free(p);
	ft_putstr_fd("minishell: ", 2);
	perror(scall);
	msh_free(data);
	exit(EXIT_FAILURE);
}

void	msh_persignal(char *scall, int sigvalue, void *p)
{
	free(p);
	ft_putstr_fd("minishell: ", 2);
	perror(scall);
	g_cmd_status = sigvalue;
}

int	msh_allocate(t_data *data)
{
	data->signals = malloc(sizeof(struct sigaction));
	if (!data->signals)
		return (1);
	ft_memset(data->signals, 0, sizeof(struct sigaction));
	if (!set_env(data))
		return (1);
	data->relative_path = get_var("PWD", data);
	data->old_path = ft_strdup(data->relative_path);
	if (!data->relative_path || !data->old_path)
		return (1);
	return (0);
}

int	msh_init(t_data *data)
{
	data->signals->sa_sigaction = sig_info_main;
	data->input = NULL;
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
	data->signals = NULL;
	data->env_str = NULL;
	data->relative_path = NULL;
	data->old_path = NULL;
	if (msh_allocate(data))
		msh_exit(data, 1);
	return (0);
}
