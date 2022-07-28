/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:00:30 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/29 01:01:16 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_cmd_status;

void	execute(t_data *data)
{
	t_cmd	*cmd;
	t_list	*c_idx;
	pid_t	wpid;

	alloc_pipes(data);
	c_idx = data->cmd;
	while (c_idx != NULL)
	{
		cmd = c_idx->content;
		if (c_idx->next != NULL)
			init_pipe(data, cmd->i);
		if (!cmd->to_fork)
			run_cmd(data, cmd, cmd->i, data->n_cmd);
		else
			run_forked_cmd(data, cmd);
		c_idx = c_idx->next;
	}
	close_pipes(data->pips, data->n_cmd - 1);
	wpid = 1;
	while (data->child > 0)
		data->child = waitpid(data->child, &g_cmd_status, 0);
	g_cmd_status = WEXITSTATUS(g_cmd_status);
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
	else if (cmd->fin != -1 && !dup_close(cmd->fin, STDIN_FILENO))
		msh_exit(data);
	if (cmd->fout == -1 && i != n - 1 && n > 1)
		dup2(data->pips[w].fd[1], STDOUT_FILENO);
	else if (cmd->fout != -1 && !dup_close(cmd->fout, STDOUT_FILENO))
		msh_exit(data);
	close_unused_pipes(data->pips, r, w, n);
	if (cmd->builtin)
		exec_builtin(data, cmd);
	else if (execve(cmd->fullpath, cmd->args, data->env_str) == -1)
	{
		exec_error(cmd);
		msh_exit(data);
	}
}

void	exec_error(t_cmd *cmd)
{
	int		fdtest;

	fdtest = -1;
	if (!cmd->fullpath)
		cmd_notfound(cmd->name);
	else if (open(cmd->fullpath, O_WRONLY | O_APPEND) == -1
		|| access(cmd->fullpath, X_OK) == -1)
	{
		perror("minishell: ");
		g_cmd_status = 126;
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
