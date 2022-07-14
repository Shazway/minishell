/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:00:30 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/14 20:03:16 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute(t_data *data)
{
    t_cmd   *to_execute;
    t_list  *c_idx;
	int		p_idx;
	int		pid;

	p_idx = 0;
    c_idx = data->cmd;
    while (c_idx != NULL)
    {
		if (c_idx->next != NULL)
		{
			if (pipe(data->pips[p_idx].fd) == (-1))
			{
				//cmdarg_free(&data, p_idx, n_cmd);
				//perrxit("Error");
			}
		}
        to_execute = data->cmd->content;
        pid = fork();
		if (pid == -1)
		{

		}
		else if (pid == 0)
			run_cmd();
		c_idx = c_idx->next;
		p_idx++;
	}
	//cmdarg_free(&data, i, n_cmd);
	//i = 0;
	//while (i < n_cmd)
//	{
//		wait(NULL);
//		i++;
//	}
}

void	run_cmd(t_data *data, t_cmd *cmd, int c_idx, t_list *next)
{
	int		r;
	int		w;
	int		j;

	if (c_idx == 0)
		r = c_idx;
	else
		r = c_idx - 1;
	if (next == NULL)
		w = c_idx - 1;
	else
		w = c_idx;
	if (c_idx == 0)
	{
		dup2(data->finput,STDIN_FILENO);
		close(finput);
	}
	else
		dup2(cmd->pips[r].fd[0], STDIN_FILENO);
	j = 0;
	while (j <= r)
	{
		close(cmd->pips[j].fd[0]);
		j++;
	}
	
	
	if (c_idx == n - 1)
	{
		dup2(foutput, STDOUT_FILENO);
		close(foutput);
	}
	else
	{
		dup2(cmd->pips[w].fd[1], STDOUT_FILENO);
	}
	j = 0;
	while (j <= w)
	{
		close(cmd->pips[j].fd[1]);
		j++;
	}
	if (execve(cmd->cmd_path[c_idx], cmd->cmd_args[c_idx], cmd->envr) == -1)
	{
		cmdarg_free(cmd, c_idx, n);
		if (!cmd->cmd_path[c_idx])
			cmd_notfound();
		else
			perrxit("Error");
	}
}


void	search_cmds(t_data *data, t_cmd *cmd)
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

char	*get_path(char *c_name, char **envr)
{
	char	*fullpath;
	int		j;

	fullpath = getpath_worker(c_name, envr);
	if (!fullpath)
	{
		free(fullpath);
		return ;
	}
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
		free_arraystr(path_array);
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

