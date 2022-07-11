/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:24:49 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/11 15:18:06 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct sigaction	g_signals;

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
		printf("^C\n\n");
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
