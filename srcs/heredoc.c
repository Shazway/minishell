/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:00:16 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/29 12:01:09 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *lim, int expand, t_data *data)
{
	int		fd;
	char	*buf;
	char	*p;
	int		len_lim;
	int		stdin_copy;

	stdin_copy = dup(0);
	if (stdin_copy == -1)
		msh_perexit(data, "dup");
	expand = 1;
	if (ft_strchr(lim, '"') || ft_strchr(lim, '\''))
		expand = 0;
	if (!expand)
		lim = del_quote(lim);
	if (!lim)
		msh_exit(data);
	fd = open("/tmp/msh_here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd)
	{
		perror("open");
		g_cmd_status = 126;
	}
	len_lim = ft_strlen(lim);
	while (fd)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		p = ft_strnstr(buf, lim, len_lim);
		if (p && p == buf && p[len_lim] == '\0')
		{
			free(buf);
			break ;
		}
		if (!heredoc_writer(fd, buf, expand, data))
		{
			free(buf);
			free(lim);
			msh_exit(data);
		}
		free(buf);
	}
	free(lim);
	dup2(stdin_copy, 0);
	close(stdin_copy);
	close(fd);
	fd = open("/tmp/msh_here_doc", O_RDONLY);
	return (fd);
}

int		heredoc_writer(int fd, char *buf, int expand, t_data *data)
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
			value = find_var(data->env_str, var);
			if (!value)
				return (0);
			free(value);
			free(var);
			p = ft_strchr(buf + from, '$');
		}
	}
	if (!expand || !p)
		ft_putendl_fd(buf + from, fd);
	return (1);
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

void	heredoc_handler(int signal, siginfo_t *s, void *trash)
{
	(void)trash;
	(void)s;

	if (signal == SIGINT)
	{
		write(1, "^C\n", 4);
		g_cmd_status = 130;
		close(0);
		
	}
	if (signal == SIGQUIT)
	{
		g_cmd_status = 0;
		return ;
	}
	if (signal == SIGCHLD)
		return ;
}
