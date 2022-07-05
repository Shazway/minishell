/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:59:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/05 16:49:57 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_result(t_token *token)
{
	int i;

	i = 0;
	while (token->str_split && token->str_split[i])
	{
		printf("[%s]\n", token->str_split[i]);
		i++;
	}
}

void	split_spaces(t_token *token, char *content)
{
	token->str_split = ft_split(content, ' ');
	token->str = NULL;
	token->name = NULL;
	token->content = NULL;
	print_result(token);
}

void	del_token(void *content)
{
	t_token *token;

	token = (t_token *)content;
	ft_free_tab(token->str_split);
	free(token->str);
	free(token->content);
	free(token->name);
	free(token);
}

void	check_redirect(t_data *data)
{
	t_list	*start;
	t_list	*temp;

	start = data->cmd;
	while (start->next)
	{
		
	}
}

int	parsing(t_data *data)
{
	int 	i;
	t_token *temp;
	t_list	**test = &data->cmd;
	char	**pipe_split;

	i = 0;
	data->input = ft_strtrim(data->input, " ");
	arrange_redirections(data);
	pipe_split = ft_split(data->input, '|');
	while (pipe_split[i])
	{
		temp = malloc(sizeof(t_token));
		if (!temp)
			return (1);
		ft_lstadd_back(test, ft_lstnew((void *)temp));
		split_spaces(temp, pipe_split[i]);
		printf("New command\n");
		i++;
	}
	check_redirect(data);
	ft_lstclear(&(data->cmd), del_token);
	ft_free_tab(pipe_split);
	return (i);
}
