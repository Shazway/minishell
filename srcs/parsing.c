/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:59:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/16 20:59:06 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char	*str, int *type)
{
	if (str && (str[0] == ' ' || str[0] == ' '))
		return (*type);
	if (!ft_strncmp(str, ">", 4))
		*type = R_DIR;
	if (!ft_strncmp(str, ">>", 4))
		*type = R_DDIR;
	if (!ft_strncmp(str, "<", 4))
		*type = L_DIR;
	if (!ft_strncmp(str, "<<", 4))
		*type = L_DDIR;
	return (*type);
}

int	setup_rfiles(t_cmd	*arg, int type, int i)
{
	char	*work_path;
	int		*trash;

	*trash = 0;
	if (!arg->args[i + 1] || is_redirection(arg->args[i + 1], &trash))
		return (printf("minishell:syntax error near unexpected token`newline'\n"));
	work_path = pwd();
	if (type == R_DIR)
	{
		arg->fin = open(concat_path(work_path,
			arg->args[i + 1]), O_CREAT, O_TRUNC, O_WRONLY);
	}
	if (type == R_DDIR)
	{
		arg->fin = open(concat_path(work_path,
			arg->args[i + 1]), O_CREAT, O_APPEND, O_WRONLY);
	}
	if (type == L_DIR)
	{
		if (i == 0)
			arg->fout = -1;
		else
			arg->fout = open(concat_path(work_path, arg->args[i]), O_RDONLY);
	}
	if (type == L_DDIR)
		here_doc(arg->args[i + 1], &arg->fin);
	free(work_path);
	return (1);
}

int	open_redirections(t_data	*data)
{
	int		i;
	t_cmd	*arg;
	t_list	*tmp;
	int		*type;

	i = 0;
	tmp = data->cmd;
	while (data->cmd && data->cmd->next)
	{
		*type = 0;
		arg = data->cmd->content;
		while (arg->args && arg->args[i])
		{
			if (is_redirection(arg->args[i], &type))
				setup_rfiles(arg, type, i);
			i++;
		}
		data->cmd = data->cmd->next;
	}
	data->cmd = tmp;
}

int	parsing(t_data *data)
{
	int		i;
	t_cmd	*temp;
	char	**pipe_split;

	i = 0;
	data->input = separate_redir(data->input);
	pipe_split = unquote_split(data->input, '|');
	while (pipe_split[i])
	{
		temp = malloc(sizeof(t_cmd));
		if (!temp)
			return (1);
		ft_lstadd_back(&(data->cmd), ft_lstnew((void *)temp));
		temp->lim = NULL;
		split_spaces(temp, pipe_split[i]);
		printf("New command\n");
		i++;
	}
	data->n_cmd = i;
	str_arr_free(pipe_split);
	return (i);
}

void	print_result(t_cmd *token)
{
	int	i;

	i = 0;
	while (token->args && token->args[i])
	{
		printf("[%s]\n", token->args[i]);
		i++;
	}
}

void	split_spaces(t_cmd *token, char *content)
{
	token->args = unquote_split(content, ' ');
	token->cmd = token->args[0];
	token->ac = str_arr_size(token->args);
	print_result(token);
}

void	del_token(void *content)
{
	t_cmd	*token;

	token = (t_cmd *)content;
	str_arr_free(token->args);
	free(token);
}
