/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/10 17:20:34 by tmoragli         ###   ########.fr       */
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

void	prompt_loop(t_data *data)
{
	if (signal_intercept())
		exit(1);
	data->input = readline("\033[1;32m""➜ ""\033[1;36m"" minishell ""\033[0m");
	if (!data->input)
		exit(printf("exit\n"));
	if (ft_strlen(data->input) >= 2)
	{
		printf("[%s]\n", data->input);
		add_history(data->input);
		parsing(data);
	}
	else
		printf("[[%c]]\n", data->input[0]);
	free(data->input);
}

int    ft_free(t_data *data)
{
    if (data->cmd)
        free(data->cmd);
    return (1);
}

int    ft_allocate(t_data *data)
{
    data->cmd = NULL;
    return (0);
}

void    sig_info(int signal, siginfo_t *s, void *trash)
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
	int rc;

	rc = tcgetattr(0, &data->termios);
	if (rc)
		return (1);
	data->termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &data->termios);
	if (rc)
		return (1);
	return (0);
}

int	main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (termios_setup(data))
	{
		free(data);
		return (1);
	}
	g_signals.sa_sigaction = sig_info;
	if (ft_allocate(data))
		return (1);
	while (1)
		prompt_loop(data);
	clear_history();
	free(data);
	return (0);
}
