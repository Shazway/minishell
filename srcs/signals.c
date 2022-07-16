/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:24:49 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/16 21:01:42 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct sigaction g_signals;

int	signal_intercept(void)
{
	if (sigaction(SIGINT, &(g_signals), NULL) == -1)
		return (1);
	if (sigaction(SIGQUIT, &(g_signals), NULL) == -1)
		return (1);
	return (0);
}

void	sig_info(int signal, siginfo_t *s, void *trash)
{
	(void)trash;
	(void)s;
	if (signal == SIGINT)
	{
		printf("^C\n");
		printf("\033[1;32m""➜ ""\033[1;36m"" minishell ""\033[0m");
	}
	if (signal == SIGQUIT)
		return ;
}

int	termios_setup(t_data *data)
{
	int	rc;

	rc = tcgetattr(0, &data->termios);
	if (rc)
		return (1);
	data->termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &data->termios);
	if (rc)
		return (1);
	return (0);
}

int	msh_init(t_data *data)
{
	g_signals.sa_sigaction = sig_info;
	data->read_ret = -1;
	data->buf_trash = NULL;
	data->input = NULL;
	data->output = NULL;
	data->commands = NULL;
	data->env_str = NULL;
	data->pips = NULL;
	if (set_env(data))
		return (1);
	data->cmd = NULL;
	
	return (0);
}