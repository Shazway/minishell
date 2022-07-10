/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:59:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/11 00:35:33 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_data *data)
{
	int		i;
	char	*tmp;
	t_cmd	*temp;
	char	**pipe_split;

	i = 0;
	tmp = data->input;
	data->input = ft_strtrim(data->input, " ");
	free(tmp);
	pipe_split = unquote_split(data->input, '|');
	while (pipe_split[i])
	{
		temp = malloc(sizeof(t_cmd));
		if (!temp)
			return (1);
		ft_lstadd_back(&(data->cmd), ft_lstnew((void *)temp));
		split_spaces(temp, pipe_split[i]);
		printf("New command\n");
		i++;
	}
	ft_lstclear(&(data->cmd), del_token);
	str_arr_free(pipe_split);
	return (i);
}

void	print_result(t_cmd *token)
{
	int i;

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
	token->ac = count_tab_str(token->args);
	print_result(token);
}

void	del_token(void *content)
{
	t_cmd *token;

	token = (t_cmd *)content;
	str_arr_free(token->args);
	free(token);
}

