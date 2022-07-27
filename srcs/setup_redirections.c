/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:07:43 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/28 01:05:29 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_rfiles(t_cmd	*arg, int i, char **envr, t_data *data)
{
	char	*work_path;
	char	*final_path;
	int		type;

	type = is_redirection(arg->args[i], 0);
	work_path = ft_strdup(data->relative_path);
	final_path = concat_path(work_path, arg->args[i + 1]);
	if (!final_path)
	{
		free(work_path);
		return (0);
	}
	if (arg->fout != -1)
		close(arg->fout);
	if (arg->fin != -1)
		close(arg->fin);
	if (type == R_DIR)
		arg->fout = open(final_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (type == R_DDIR)
		arg->fout = open(final_path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (type == L_DIR)
		arg->fin = open(final_path, O_RDONLY);
	free(final_path);
	if (type == L_DDIR)
	{
		if (arg->args[i + 1])
		{
			memset(&g_signals, 0, sizeof(struct sigaction));
			g_signals.sa_sigaction = heredoc_handler;
			signal_intercept();
			arg->fin = here_doc(ft_strdup(arg->args[i + 1]), 1, envr, data);
			memset(&g_signals, 0, sizeof(struct sigaction));
			g_signals.sa_sigaction = sig_info_main;
			signal_intercept();
		}
	}
	return (1);
}

int	str_arr_size_r(char	**str)
{
	int	i;
	int	size;
	int	type;

	size = str_arr_size(str);
	i = 0;
	type = 0;
	while (str && str[i])
	{
		type = is_redirection(str[i], 0);
		if (type)
			size--;
		if (str[i + 1] && (type == R_DDIR || type == R_DIR))
			size--;
		if (str[i + 1] && (type == L_DIR || type == L_DDIR))
			size--;
		i++;
	}
	return (size);
}

char	**destroy_redirections(char **dest, char **args)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (args && args[i])
	{
		if (is_redirection(args[i], 0))
		{
			if (args[i])
				i++;
			if (args[i])
				i++;
			continue ;
		}
		else if (args[i])
		{
			dest[j] = ft_strdup(args[i]);
			j++;
		}
		if (!args[i])
			break ;
		i++;
	}
	return (dest);
}

char	**eliminate_redirections(char **args)
{
	int		size;
	char	**dest;

	size = str_arr_size_r(args);
	if (size <= 0)
	{
		str_arr_free(args);
		return (NULL);
	}
	if (size == str_arr_size(args))
		return (args);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = NULL;
	dest = destroy_redirections(dest, args);
	str_arr_free(args);
	return (dest);
}

int	open_redirections(t_data *data)
{
	int		i;
	t_cmd	*arg;
	t_list	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		arg = tmp->content;
		i = 0;
		while (arg->args && arg->args[i])
		{
			if (is_redirection(arg->args[i], 0))
			{
				if (!setup_rfiles(arg, i, data->env_str, data))
					msh_exit(data);
				i++;
			}
			if (arg->args[i])
				i++;
		}
		arg->args = eliminate_redirections(arg->args);
		if (arg->args)
		{
			free(arg->name);
			arg->name = ft_strdup(arg->args[0]);
		}
		tmp = tmp->next;
	}
	return (1);
}
