/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:59:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/16 18:04:09 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		temp->n_fin = 0;
		temp->n_fout = 0;
		ft_lstadd_back(&(data->cmd), ft_lstnew((void *)temp));
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
