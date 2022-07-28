/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:24:49 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/28 22:57:57 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	signal_intercept(t_data *data)
{
	if (sigaction(SIGCHLD, data->signals_test, NULL) == -1)
		return (1);
	if (sigaction(SIGINT, data->signals_test, NULL) == -1)
		return (1);
	if (sigaction(SIGQUIT, data->signals_test, NULL) == -1)
		return (1);
	return (0);
}

void	heredoc_handler(int signal, siginfo_t *s, void *trash)
{
	(void)trash;
	(void)s;

	if (signal == SIGINT)
	{
		write(1, "^C\n", 4);
		close(0);
		
	}
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGCHLD)
		return ;
}

void	secondary_handler(int signal, siginfo_t *s, void *trash)
{
	(void)s;
	(void)trash;
	if (signal == SIGINT)
	{
		wait(NULL);
		return ;
	}
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGCHLD)
		return ;
}

void	sig_info_main(int signal, siginfo_t *s, void *trash)
{
	(void)s;
	(void)trash;
	if (signal == SIGINT)
	{
		write(1, "^C\n", 4);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGCHLD)
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

