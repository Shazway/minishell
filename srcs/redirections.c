/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:50:41 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/01 02:31:35 by tmoragli         ###   ########.fr       */
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

void	open_redirections_worker(t_cmd *arg, char *final_path, int type, int i)
{
	if (!arg->args[0][0])
	{
		free(final_path);
		return ;
	}
	
	if (arg->fout != -1 && (type == R_DIR || type == R_DDIR))
		close(arg->fout);
	if (arg->fin != -1 && (type == L_DIR || type == L_DDIR))
		close(arg->fin);
	if (type == R_DIR)
		arg->fout = open(final_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (type == R_DDIR)
		arg->fout = open(final_path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (type == L_DIR)
		arg->fin = open(final_path, O_RDONLY);
	free(final_path);
	if (((type == R_DIR || type == R_DDIR) && arg->fout == -1)
		|| ((type == L_DIR) && arg->fin == -1))
	{
		ft_putstr_fd("minishell: ", 2);
		perror(arg->args[i + 1]);
		arg->args[0] = ft_str_zero(arg->args[0]);
	}
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
