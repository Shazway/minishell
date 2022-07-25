/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:58:13 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/25 15:19:33 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_quote(char *str)
{
	char	*new;
	int		i;
	int		size;
	int		j;

	size = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			size++;
		i++;
	}
	new = malloc(sizeof(char) * (size + 1));
	new[size] = '\0';
	i = 0;
	j = 0;
	while (j < size)
	{
		if (str[i] != '\'' && str[i] != '"')
			new[j++] = str[i];
		i++;
	}
	free(str);
	return (new);
}

void	delete_quotes(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*cmd;
	t_list	*cmd_idx;

	j = 0;
	cmd_idx = data->cmd;
	while (cmd_idx)
	{
		cmd = cmd_idx->content;
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			if (ft_strchr(cmd->args[i], '"') || ft_strchr(cmd->args[i], '\''))
				cmd->args[i] = trim_quotes(data, cmd->args[i]);
			i++;
		}
		if (cmd->args)
		{
			free(cmd->name);
			cmd->name = ft_strdup(cmd->args[0]);
		}
		cmd_idx = cmd_idx->next;
	}
}
int		trim_quote_size(char *str)
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
			{
				dest[j] = str[i];
				j++;
				i++;
			}
			type = -1;
			if (str[i])
				i++;
			continue ;
		}
		dest[j] = str[i];
		i++;
		j++;
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
		msh_exit(data);
	trimmed[size] = '\0';
	trimmed = trim_quotes_fill(trimmed, str, size);
	free(str);
	return(trimmed);
}
