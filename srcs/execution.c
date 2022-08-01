/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:00:30 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/08/02 00:09:50 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_cmd_status;

void	execute(t_data *data)
{
	t_cmd	*cmd;
	t_list	*c_idx;

	alloc_pipes(data);
	c_idx = data->cmd;
	while (c_idx != NULL)
	{
		cmd = c_idx->content;
		if (!cmd->name[0])
		{
			c_idx = c_idx->next;
			continue ;
		}
		if (c_idx->next != NULL)
			init_pipe(data, cmd->i);
		if (!cmd->to_fork)
			run_cmd(data, cmd, cmd->i, data->n_cmd);
		else
			run_forked_cmd(data, cmd);
		c_idx = c_idx->next;
	}
	close_pipes(data->pips, data->n_cmd - 1);
	data->child = waitpid(-1, &g_cmd_status, 0);
	while (data->child > 0)
	{
		if (g_cmd_status != 127 && g_cmd_status != 126)
			g_cmd_status = WEXITSTATUS(g_cmd_status);
		data->child = waitpid(-1, &g_cmd_status, 0);
	}
	reset_signal_handler(data, 0);
}

void	run_forked_cmd(t_data *data, t_cmd *cmd)
{
	data->child = fork();
	if (data->child == -1)
		return ;
	else if (data->child == 0)
		run_cmd(data, cmd, cmd->i, data->n_cmd);
	else
		reset_signal_handler(data, 1);
}

void	run_cmd(t_data *data, t_cmd *cmd, int i, int n)
{
	int		r;
	int		w;

	r = i - 1 + 1 * ((n - i) / n);
	w = i - 1 * (i == n - 1);
	if (cmd->fin == -1 && i != 0 && n > 1)
		dup2(data->pips[r].fd[0], STDIN_FILENO);
	else if (cmd->fin != -1 && !dup2_close(cmd->fin, STDIN_FILENO))
		msh_exit(data, 0);
	if (cmd->fout == -1 && i != n - 1 && n > 1)
		dup2(data->pips[w].fd[1], STDOUT_FILENO);
	else if (cmd->fout != -1 && !dup2_close(cmd->fout, STDOUT_FILENO))
		msh_exit(data, 0);
	close_unused_pipes(data->pips, r, w, n);
	if (cmd->builtin)
		exec_builtin(data, cmd);
	else if (execve(cmd->fullpath, cmd->args, data->env_str) == -1)
	{
		exec_error(cmd);
		msh_exit(data, 0);
	}
}

void	exec_error(t_cmd *cmd)
{
	int		fdtest;
	int		acc;

	fdtest = -1;
	if (!cmd->fullpath[0])
	{
		ft_putstr_fd("minishell: ", 2);
		cmd_notfound(cmd->name);
	}
	if (cmd->fullpath && cmd->fullpath[0])
	{
		acc = access(cmd->fullpath, X_OK);
		fdtest = open(cmd->fullpath, O_WRONLY | O_APPEND);
		if (acc == -1 || fdtest == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->fullpath);
			g_cmd_status = 126;
		}
	}
	if (fdtest != -1)
		close(fdtest);
}

void	close_unused_pipes(t_pipex *pips, int r, int w, int n)
{
	int	i;

	i = 0;
	while (i <= r && n > 1)
		close(pips[i++].fd[0]);
	i = 0;
	while (i <= w && n > 1)
		close(pips[i++].fd[1]);
}
