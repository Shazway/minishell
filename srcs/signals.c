/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:24:49 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/26 21:59:13 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct sigaction	g_signals;

int	signal_intercept(void)
{
	if (sigaction(SIGCHLD, &(g_signals), NULL) == -1)
		return (1);
	if (sigaction(SIGINT, &(g_signals), NULL) == -1)
		return (1);
	if (sigaction(SIGQUIT, &(g_signals), NULL) == -1)
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

t_cmd	*init_cmd(int i)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->i = i;
	cmd->ac = 0;
	cmd->to_fork = 1;
	cmd->builtin = 0;
	cmd->fin = -1;
	cmd->fout = -1;
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->fullpath = NULL;
	return (cmd);
}
