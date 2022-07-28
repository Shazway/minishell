/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:50:41 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/28 19:38:29 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char	*str, int type)
{
	if (!str || (str && (str[0] == '"' || str[0] == 39)))
		return (type);
	if (!ft_strncmp(str, ">", 2))
		type = R_DIR;
	if (!ft_strncmp(str, ">>", 3))
		type = R_DDIR;
	if (!ft_strncmp(str, "<", 2))
		type = L_DIR;
	if (!ft_strncmp(str, "<<", 3))
		type = L_DDIR;
	return (type);
}

char	*concat_redir(char *str, char *redir, int *i, int is_double)
{
	char	*end;
	char	*trash;
	char	*here;

	if (i == 0)
		return (str);
	end = ft_substr(str, (*i + is_double), ft_strlen(str));
	if (!end)
		return (NULL);
	here = ft_substr(str, 0, *i);
	if (!here)
	{
		free(end);
		return (NULL);
	}
	trash = str;
	str = ft_strjoin(here, redir);
	free(here);
	free(trash);
	trash = str;
	str = ft_strjoin(str, end);
	free(trash);
	*i += (ft_strlen(redir));
	free(end);
	if (!str)
		return (NULL);
	return (str);
}

char	*check_redir(char *str, int *i)
{
	if (str && str[*i] && str[*i + 1] && str[*i] == '>')
	{
		if (str[*i + 1] != '>')
			str = concat_redir(str, " > ", i, 1);
		else
			str = concat_redir(str, " >> ", i, 2);
		if (!str)
			return (NULL);
	}
	if (str && str[*i] && str[*i + 1] && str[*i] == '<')
	{
		if (str[*i + 1] != '<')
			str = concat_redir(str, " < ", i, 1);
		else
			str = concat_redir(str, " << ", i, 2);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*separate_redir(char *str)
{
	int		i;
	char	*temp;
	char	type;

	type = -1;
	i = 0;
	temp = str;
	str = ft_strtrim(str, " ");
	if (!str)
		return (NULL);
	free(temp);
	while (str && str[i])
	{
		check_quote(&type, str[i]);
		if (type == -1 && (str[i] == '>' || str[i] == '<'))
		{
			str = check_redir(str, &i);
			if (!str)
				return (NULL);
			if (!str[i])
				break ;
		}
		i++;
	}
	return (str);
}
