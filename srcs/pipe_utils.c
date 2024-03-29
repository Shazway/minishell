/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:16:33 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/04 15:29:59 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_pipes(t_data *data)
{
	data->pips = malloc((data->n_cmd - 1) * sizeof(t_pipex));
	if (!data->pips)
		msh_exit(data, 1);
}

void	init_pipe(t_data *data, int i)
{
	if (pipe(data->pips[i].fd) == (-1))
		msh_perexit(data, "pipe", NULL);
}

void	free_pipes(t_data *data)
{
	close_pipes(data->pips, data->n_cmd - 1);
	free(data->pips);
	data->pips = NULL;
}

void	close_pipes(t_pipex *pips, int n)
{
	int	i;

	if (!pips)
		return ;
	i = 0;
	while (i < n)
	{
		if (pips[i].fd[0] != -1)
			close(pips[i].fd[0]);
		if (pips[i].fd[1] != -1)
			close(pips[i].fd[1]);
		i++;
	}
}

int	dup2_close(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror("pipe");
			return (0);
		}
		close(oldfd);
	}
	return (1);
}
