/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:59:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/02 19:01:40 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_data *data)
{
	int		i;
	char	**pipe_split;
	char	*tmp;

	i = 0;
	data->input = separate_redir(data->input);
	if (!data->input)
		msh_exit(data, 1);
	if (!ft_strlen(data->input))
		return (0);
	tmp = data->input;
	data->input = trim_delim(data->input, &ft_isspace);
	free(tmp);
	pipe_split = unquote_split_v2(data->input, &is_pipe);
	if (!pipe_split)
		msh_exit(data, 1);
	while (pipe_split && pipe_split[i])
	{
		fill_token(data, pipe_split, i);
		i++;
	}
	data->n_cmd = i;
	str_arr_free(pipe_split);
	return (i);
}

void	fill_token(t_data *data, char **pipe_split, int i)
{
	t_cmd	*token;

	token = init_cmd(i);
	if (!token)
	{
		ft_lstclear(&(data->cmd), &(free_cmd));
		str_arr_free(pipe_split);
		msh_exit(data, 1);
	}
	ft_lstadd_back(&(data->cmd), ft_lstnew((void *)token));
	split_spaces(token, pipe_split[i]);
	if (!token->args)
	{
		ft_lstclear(&(data->cmd), &(free_cmd));
		str_arr_free(pipe_split);
		msh_exit(data, 1);
	}
}

void	print_result(t_cmd *token)
{
	int	i;

	i = 0;
	while (token->args && token->args[i])
	{
		ft_printf("[%s]\n", token->args[i]);
		i++;
	}
}

void	split_spaces(t_cmd *token, char *content)
{
	token->args = unquote_split_v2(content, &(ft_isspace));
	if (!token->args)
		return ;
}

int	is_opened_quotes(t_data *data)
{
	char	type;
	int		i;

	i = 0;
	type = -1;
	while (data->input && data->input[i])
	{
		check_quote(&type, data->input[i]);
		i++;
	}
	if (type == -1)
		return (1);
	data->error_msh = "Unclosed quote, try closing the \" or \' quote\n";

	return (0);
}
