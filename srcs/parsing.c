/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:59:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/03 01:48:27 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_data *data)
{
	int		i;
	char	**pipe_split;

	i = 0;
	data->input = separate_redir(data->input);
	if (!data->input)
		msh_exit(data, 1);
	if (!ft_strlen(data->input))
		return (0);
	pipe_split = unquote_split(data->input, &is_pipe, 0);
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
	token->args = unquote_split(pipe_split[i], &ft_isspace, 1);
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

int	is_pipe(char c)
{
	if (!c)
		return (0);
	if (c == '|')
		return (1);
	return (0);
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
