/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:24:49 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/08/03 22:45:34 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_intercept(t_data *data)
{
	if (sigaction(SIGINT, data->signals, NULL) == -1)
		return (1);
	if (sigaction(SIGQUIT, data->signals, NULL) == -1)
		return (1);
	if (sigaction(SIGCHLD, data->signals, NULL) == -1)
		return (1);
	return (0);
}

void	reset_signal_handler(t_data *data, int i)
{
	ft_memset(data->signals, 0, sizeof(struct sigaction));
	if (i == 0)
		data->signals->sa_sigaction = sig_info_main;
	else if (i == 1)
		data->signals->sa_sigaction = secondary_handler;
	else if (i == 2)
		data->signals->sa_sigaction = heredoc_handler;
	signal_intercept(data);
}

void	child_status(void)
{
	if (g_cmd_status == 2)
		ft_putstr_fd("^C\n", 2);
	if (g_cmd_status == 131)
		ft_putstr_fd("^Quit (core dumped)\n", 2);
	if (g_cmd_status == 2)
		g_cmd_status = 130;
}

void	secondary_handler(int signal, siginfo_t *s, void *trash)
{
	(void)s;
	(void)trash;
	if (signal == SIGINT)
	{
		g_cmd_status = 130;
		wait(&g_cmd_status);
		if (g_cmd_status != 2 && g_cmd_status != 130)
			g_cmd_status = WEXITSTATUS(g_cmd_status);
		return ;
	}
	if (signal == SIGQUIT)
	{
		g_cmd_status = 131;
		wait(&g_cmd_status);
		if (g_cmd_status != 131)
			g_cmd_status = WEXITSTATUS(g_cmd_status);
		return ;
	}
	if (signal == SIGCHLD)
		child_status();
}

void	sig_info_main(int signal, siginfo_t *s, void *trash)
{
	(void)s;
	(void)trash;
	if (signal == SIGINT)
	{
		g_cmd_status = 130;
		write(1, "^C\n", 4);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
		return ;
}
