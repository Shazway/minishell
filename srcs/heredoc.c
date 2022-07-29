/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:00:16 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/29 19:06:34 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *lim, int expand, t_data *data)
{
	int		fd;
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
		msh_persignal("open", 126);
	heredoc_prompt(lim, expand, data, fd);
	free(lim);
	if (!dup2_close(stdin_copy, STDIN_FILENO))
		msh_perexit(data, "dup");
	close(fd);
	fd = open("/tmp/msh_here_doc", O_RDONLY);
	return (fd);
}

int	heredoc_prompt(char *lim, int expand, t_data *data, int fd)
{
	char	*buf;
	char	*p;
	int		len_lim;

	len_lim = ft_strlen(lim);
	while (fd)
	{
		buf = readline("> ");
		if (!buf)
			return (0);
		p = ft_strnstr(buf, lim, len_lim);
		if (p && p == buf && p[len_lim] == '\0')
			return (ft_free(buf) == NULL);
		if (!heredoc_writer(fd, buf, expand, data))
		{
			ft_free_strs(&buf, &lim, NULL, NULL);
			msh_exit(data);
		}
		free(buf);
	}
	return (0);
}

int	heredoc_writer(int fd, char *buf, int expand, t_data *data)
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
			ft_putstr_fd(value, fd);
			ft_free_strs(&value, &var, NULL, NULL);
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
