/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:00:30 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/18 16:06:45 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_cmds(t_data *data)
{
	t_list	*i;
	t_cmd	*current_cmd;
	char	*fullpath;

	i = data->cmd;
	while (i != NULL)
	{
		current_cmd = i->content;
		if (!is_builtin(current_cmd->cmd))
		{
			fullpath = get_path(current_cmd->cmd, data->env_str);
			if (fullpath)
			{
				free(current_cmd->fullpath);
				current_cmd->fullpath = fullpath;
			}
		}
		else
		{
			current_cmd->fullpath = ft_strdup(current_cmd->cmd);
		}
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
		//str_arr_display(to_execute->args);
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
		close(to_execute->fin);
		wait(NULL);
	//	waitpid()
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
		printf("fin %d\n", cmd->fin);
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
		if (!cmd->fullpath)
			cmd_notfound();
		exit(EXIT_FAILURE);
	//	else
		//	perrxit("Error");
	}
}

int	execmd(int ac, char *fullpath, char **args, t_data *data)
{
	int	ret;

	ret = 1;
	if (!ft_strncmp(fullpath, "echo", 4))
	{
		ft_echo(ac, args + 1);
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strncmp(fullpath, "cd", 2))
		cd(ac, args + 1);
	else if (!ft_strncmp(fullpath, "pwd", 3))
		pwd();
	else if (!ft_strncmp(fullpath, "export", 6))
		pwd();
	else if (!ft_strncmp(fullpath, "unset", 5))
		pwd();
	else if (!ft_strncmp(fullpath, "env", 3))
		pwd();
	else if (!ft_strncmp(fullpath, "exit", 4))
		shell_exit(ac, args + 1);
	else
	{
		ret = execve(fullpath, args, data->env_str);
	}
	return (ret);
}

char	*get_path(char *c_name, char **envr)
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
		return (NULL);
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

	p = NULL;
	if (expand)
	{
		p = ft_strchr(buf, '$');
		if (p)
		{
			write(fd, buf, p - buf);
			//printf("p = %s\n", p);
			var = extract_var(p + 1);
			//printf("var = %s\n", var);
			ft_putstr_fd(find_var(envr, var), fd);
		//	printf("value %s\n", find_var(envr, var));
			ft_putendl_fd(p + ft_strlen(var) + 1, fd);
		}
	}
	if (!expand || !p)
		ft_putendl_fd(buf, fd);
}

char	*extract_var(char *pvar)
{
	int		to;
	char	*var;

	to = is_validid(pvar, -1);
	//printf("to %d %s\n", to, pvar);
	if (to > 0)
	{
		var = ft_substr(pvar, 0, to);
		return (var);
	}
	return (NULL);

}