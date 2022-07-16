/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:00:30 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/16 22:05:44 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_cmds(t_data *data)
{
	t_list	*i;
	t_cmd	*current_cmd;

	i = data->cmd;
	while (i != NULL)
	{
		current_cmd = i->content;
		if (!is_builtin(current_cmd->cmd))
			current_cmd->fullpath = get_path(current_cmd->cmd, data->env_str);
		i = i->next;
	}
}

int	is_builtin(char *c_name)
{
	char	*builtins[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int		i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(builtins[i], c_name, ft_strlen(c_name)))
			return (1);
		i++;
	}
	return (0);
}

void    execute(t_data *data)
{
    t_cmd   *to_execute;
    t_list  *c_idx;
	int		i;
	int		pid;

	i = 0;
    c_idx = data->cmd;
	data->pips = malloc((data->n_cmd - 1) * sizeof(t_pipex));
    while (c_idx != NULL)
    {
		if (c_idx->next != NULL)
			if (pipe(data->pips[i].fd) == (-1))
				return ;
		to_execute = c_idx->content;
        pid = fork();
		if (pid == -1)
			return ;
		else if (pid == 0)
			run_cmd(data, to_execute, i, data->n_cmd);
		c_idx = c_idx->next;
		i++;
	}
	i = 0;
	c_idx = data->cmd;
	while (c_idx->next != NULL)
	{
		close(data->pips[i].fd[0]);
		close(data->pips[i].fd[1]);
		c_idx = c_idx->next;
		i++;
	}
	c_idx = data->cmd;
	to_execute = c_idx->content;
	while (c_idx != NULL)
	{
		//close(to_execute->fin)
		wait(NULL);
		c_idx = c_idx->next;
	}
}

void	run_cmd(t_data *data, t_cmd *cmd, int c_idx, int n_cmd)
{
	int		r;
	int		w;
	int		j;

	if (c_idx == 0)
		r = c_idx;
	else
		r = c_idx - 1;
	if (c_idx == n_cmd - 1)
		w = c_idx - 1;
	else
		w = c_idx;
	
	if (cmd->fin == -1)
	{
		if (c_idx != 0 && data->n_cmd > 1)
		{
			dup2(data->pips[r].fd[0], STDIN_FILENO);
			printf("c_idx %d\t n_cmd %d\n", c_idx, n_cmd);
		}
	}
	else
	{
		dup2(cmd->fin, STDIN_FILENO);
		close(cmd->fin);
	}
	j = 0;
	while (j <= r && data->n_cmd > 1)
		close(data->pips[j++].fd[0]);
	if (cmd->fout == -1)
	{
		
		if (c_idx != n_cmd - 1 && data->n_cmd > 1)
		{
			
			dup2(data->pips[w].fd[1], STDOUT_FILENO);
			
		}
	}
	else
	{

		dup2(cmd->fout, STDOUT_FILENO);
		close(cmd->fout);
	}
	j = 0;
	while (j <= w && data->n_cmd > 1)
		close(data->pips[j++].fd[1]);
	if (execve(cmd->fullpath, cmd->args, data->env_str) == -1)
	{
		
		//msh_free(data);
		if (!cmd->fullpath)
			cmd_notfound();
	//	else
		//	perrxit("Error");
	}
}

char	*get_path(char *c_name, char **envr)
{
	char	*fullpath;

	fullpath = getpath_worker(c_name, envr);
	return (fullpath);
}

char	*getpath_worker(char *c_name, char **envr)
{
	int		i;
	char	*path_var;
	char	**path_array;
	char	*working_cmd;

	i = 0;
	if (envr[0])
	{
		while (envr[i] != NULL)
		{
			path_var = ft_strnstr(envr[i], "PATH=", 5);
			if (path_var != NULL)
				break ;
			i++;
		}
		if (!path_var)
			return (NULL);
		path_var += 5;
		path_array = ft_split(path_var, ':');
		working_cmd = parse_path(path_array, c_name);
		str_arr_free(path_array);
		if (working_cmd)
			return (working_cmd);
	}
	return (NULL);
}

char	*parse_path(char **path_array, char *c_name)
{
	int		i;
	char	*working_cmd;
	char	*slashcmd;
	int		found;

	slashcmd = ft_strjoin("/", c_name);
	found = 0;
	i = 0;
	while (!found && path_array && path_array[i] != NULL)
	{
		working_cmd = ft_strjoin(path_array[i++], slashcmd);
		if (access(working_cmd, F_OK) == 0)
			found = 1;
		if (!found)
			free(working_cmd);
	}
	free(slashcmd);
	if (found)
		return (working_cmd);
	else
	{
		working_cmd = malloc(1 * sizeof(char));
		return (working_cmd);
	}
}

void print_fullpath(t_data *data)
{
	t_list *i;
	t_cmd	*cmd;

	i = data->cmd;
	cmd = (t_cmd *)i->content;
	while (i != NULL)
	{
		cmd = (t_cmd *) i->content;
		printf("fullpath: %s\n", cmd->fullpath);
		i = i->next;
	}
}

void	cmd_notfound(void)
{
	ft_putendl_fd("Error: command not found", 2);
	exit(EXIT_FAILURE);
}
/*
int		here_doc(char *lim)
{
	int		i;
	char	*buf;

	i = 0;
	while (true)
	{
		buf = readline(">");
		if (!buf)
		{
			printf("signal\n");
			break ;
		}
		ft_strnstr()
		i++;
	}
}
*/