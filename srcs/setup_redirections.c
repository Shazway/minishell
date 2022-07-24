/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:07:43 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/24 11:26:02 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	str_arr_display(dest);
	return (dest);
}

char	**eliminate_redirections(char **args)
{
	int		size;
	char	**dest;

	size = str_arr_size_r(args);
	if (size <= 0)
		return (NULL);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = NULL;
	dest = destroy_redirections(dest, args);
	str_arr_free(args);
	return (dest);
}

int	setup_rfiles(t_cmd	*arg, int i, char **envr, t_data *data)
{
	char	*work_path;
	char	*final_path;
	int		type;

	type = is_redirection(arg->args[i], 0);
	work_path = ft_strdup(data->relative_path);
	final_path = concat_path(work_path, arg->args[i + 1]);
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
	if (type == L_DDIR)
	{
		//arg->heredocs = 1;
		/*arg->lim = arg->args[i + 1];
		//arg->lim = check_quote_lim(arg->args[i + 1]);*/
		memset(&g_signals, 0, sizeof(struct sigaction));
		g_signals.sa_sigaction = heredoc_handler;
		signal_intercept();
		arg->fin = here_doc(ft_strdup(arg->args[i + 1]), 1, envr);
		memset(&g_signals, 0, sizeof(struct sigaction));
		g_signals.sa_sigaction = sig_info_main;
		signal_intercept();
	}
	str_arr_display(arg->args);
	free(final_path);
	return (1);
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
				setup_rfiles(arg, i, data->env_str, data);
				i++;
			}
			if (arg->args[i])
				i++;
		}
		arg->args = eliminate_redirections(arg->args);
		tmp = tmp->next;
	}
	return (1);
}
