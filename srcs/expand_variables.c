/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:31:17 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/02 23:37:11 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_list(t_data *data)
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
			if (ft_strchr(cmd->args[i], '$'))
				cmd->args[i] = expand_variables(data, cmd->args[i], -1);
			if (!cmd->args[i])
				msh_exit(data, 1);
			i++;
		}
		cmd_idx = cmd_idx->next;
	}
}

char	*expand_variables(t_data *data, char *str, char type)
{
	char	*start;
	char	*end;
	int		i;
	char	*true_var;

	i = 0;
	while (str && str[i])
	{
		true_var = NULL;
		check_quote(&type, str[i]);
		if ((str[i] == '$' && type != '\'') && !is_expand(str[i + 1]))
		{
			if (!get_start_unquote(str, &start))
				msh_exit(data, 1);
			end = replace_variables(ft_substr(str, i,
						ft_strlen(str) - i), data, NULL, &true_var);
			if (!end)
				return (ft_free(start));
			free(str);
			str = ft_strjoin(start, end);
			free(start);
			free(end);
			if (!str)
				return (NULL);
			if (true_var[0])
				i += ft_strlen(true_var);
			free(true_var);
			continue ;
		}
		i++;
	}
	return (str);
}
