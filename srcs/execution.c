/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:00:30 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/19 22:47:22 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (to_execute->no_fork)
		{
			run_cmd(data, to_execute, i, data->n_cmd);
		}
		else
		{
        	pid = fork();
			if (pid == -1)
				return ;
			else if (pid == 0)
			{
				printf("msh : %s\n", to_execute->name);
				run_cmd(data, to_execute, i, data->n_cmd);
			}
		}
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
		close(to_execute->fin);
		if (!nofork_builtin(to_execute->name))
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
	if (execmd(cmd->ac, cmd->fullpath, cmd->args, data) == -1)
	{
		//msh_free(data);
		cmd_notfound(cmd->name);
		exit(EXIT_FAILURE);
	//	else
		//	perrxit("Error");
	}
}

int	execmd(int ac, char *fullpath, char **args, t_data *data)
{
	int		ret;
	char	*tmp;



	ret = 1;
	if (!ft_strncmp(fullpath, "echo", 4))
	{
		ft_echo(ac, args + 1);
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strncmp(fullpath, "cd", 2))
		cd(ac, args + 1, data);
	else if (!ft_strncmp(fullpath, "pwd", 3))
	{
		tmp = pwd(data);
		printf("%s\n", tmp);
		free(tmp);
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strncmp(fullpath, "export", 6))
	{
		ft_export(data, ac, args);
	}
	else if (!ft_strncmp(fullpath, "unset", 5))
		exit(EXIT_SUCCESS);
	else if (!ft_strncmp(fullpath, "env", 3))
	{
		ft_env(data, ac);
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strncmp(fullpath, "exit", 4))
		shell_exit(ac, args + 1);
	else
	{
		ret = execve(fullpath, args, data->env_str);
	}
	return (ret);
}

void	cmd_notfound(char *cmd_name)
{
	printf("%s: command not found\n", cmd_name);
}

 int	here_doc(char *lim, int expand, char **envr)
{
	int		fd;
	char	*buf;
	char	*p;
	int		len_lim;

	fd = open("/tmp/msh_here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd)
		perror("open");
	len_lim = ft_strlen(lim);
	while (fd)
	{
		buf = readline("> ");
		if (!buf)
		{
			printf("signal\n");
			break ;
		}
		p = ft_strnstr(buf, lim, len_lim);
		if (p && p == buf && p[len_lim] == '\0')
			break ;
		heredoc_writer(fd, buf, expand, envr);
	}
	close(fd);
	fd = open("/tmp/msh_here_doc", O_RDONLY);
	return (fd);
}

void	heredoc_writer(int fd, char *buf, int expand, char **envr)
{
	char	*p;
	char	*var;
	int		from;
	char	*value;

	p = NULL;
	from = 0;
	if (expand)
	{
		p = ft_strchr(buf, '$');
		while (p)
		{
			write(fd, buf + from, p - (buf + from));
			var = extract_var(p + 1);
			from += 1 + ft_strlen(var);
			value = find_var(envr, var);
			ft_putstr_fd(value, fd);
			free(value);
			free(var);
			p = ft_strchr(buf + from, '$');
		}
	}
	if (!expand || !p)
		ft_putendl_fd(buf + from, fd);
}

char	*extract_var(char *pvar)
{
	int		to;
	char	*var;

	to = is_validid(pvar, -1);
	if (to > 0)
	{
		var = ft_substr(pvar, 0, to);
		return (var);
	}
	return (NULL);
}
