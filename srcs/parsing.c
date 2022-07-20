/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:59:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/20 16:50:42 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_data *data)
{
	int		i;
	t_cmd	*token;
	char	**pipe_split;

	i = 0;
	data->input = separate_redir(data->input);
	if (!ft_strlen(data->input))
		return (0);
	pipe_split = unquote_split(data->input, '|');
	while (pipe_split && pipe_split[i])
	{
		token = init_cmd();
		if (!token)
			return (1);
		ft_lstadd_back(&(data->cmd), ft_lstnew((void *)token));
		split_spaces(token, pipe_split[i]);
		if (pipe_split[i + 1])
			printf("New command (cmd->next)\n");
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
	str_arr_display(token->args);
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
