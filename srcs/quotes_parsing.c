/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:58:13 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/01 01:50:30 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_quotes(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	t_list	*cmd_idx;

	cmd_idx = data->cmd;
	while (cmd_idx)
	{
		cmd = cmd_idx->content;
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			if (ft_strchr(cmd->args[i], '"') || ft_strchr(cmd->args[i], '\''))
				cmd->args[i] = trim_quotes(data, cmd->args[i]);
			if (!cmd->args[i])
				msh_exit(data, 1);
			i++;
		}
		cmd_idx = cmd_idx->next;
	}
}

int	trim_quote_size(char *str)
{
	int		i;
	char	type;
	int		size;

	type = -1;
	i = 0;
	size = ft_strlen(str);
	while (str && str[i])
	{
		check_quote(&type, str[i]);
		if (type != -1)
		{
			if (str[i])
				i++;
			size -= 2;
			while (str[i] && str[i] != type)
				i++;
			type = -1;
			if (str[i])
				i++;
			continue ;
		}
		i++;
	}
	return (size);
}

char	*trim_quotes_fill(char *dest, char *str, int size)
{
	int		i;
	int		j;
	char	type;

	i = 0;
	j = 0;
	type = -1;
	while (str[i] && j < size)
	{
		check_quote(&type, str[i]);
		if (type != -1)
		{
			if (str[i])
				i++;
			while (str[i] && str[i] != type)
				dest[j++] = str[i++];
			type = -1;
			if (str[i])
				i++;
			continue ;
		}
		dest[j++] = str[i++];
	}
	return (dest);
}

char	*trim_quotes(t_data *data, char *str)
{
	char	*trimmed;
	int		size;

	size = trim_quote_size(str);
	trimmed = malloc(sizeof(char) * (size + 1));
	if (!trimmed)
		msh_exit(data, 1);
	trimmed[size] = '\0';
	if (size)
		trimmed = trim_quotes_fill(trimmed, str, size);
	free(str);
	return (trimmed);
}
