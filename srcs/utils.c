/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:55:18 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/23 19:31:34 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_arr_free(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	str_arr_size(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}

void	str_arr_display(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		printf("[%s]\n", str[i]);
		i++;
	}
}

char	**str_arr_add(char **sarr, char **entry, int len_entry)
{
	int		len_sarr;
	char	**new;
	int		i;
	int		j;

	len_sarr = str_arr_size(sarr);
	new = malloc(sizeof(char *) * (len_sarr + len_entry + 1));
	if (!new)
		return (NULL);
	new[len_sarr + len_entry] = NULL;
	i = 0;
	while (i < len_sarr)
	{
		new[i] = ft_strdup(sarr[i]);
		i++;
	}
	j = 0;
	while (entry && j < len_entry)
	{
		new[i] = ft_strdup(entry[j]);
		j++;
		i++;
	}
	return (new);
}

int	ft_malloc(void **p, int length)
{
	*p = malloc(length);
	if (*p)
		return (1);
	return (0);
}

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

	i = 0;
	j = 0;
	cmd_idx = data->cmd;
	while (cmd_idx)
	{
		cmd = cmd_idx->content;
		while (cmd->args && cmd->args[i])
		{
			if (ft_strchr(cmd->args[i], '"') || ft_strchr(cmd->args[i], '\''))
				cmd->args[i] = del_quote(cmd->args[i]);
			i++;
		}
		if (cmd->args)
			cmd->name = ft_strdup(cmd->args[0]);
		cmd_idx = cmd_idx->next;
	}
}