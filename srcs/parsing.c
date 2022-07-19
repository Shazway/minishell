/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:59:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/19 21:40:35 by tmoragli         ###   ########.fr       */
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
int	str_arr_size_r(char	**str)
{
	int	i;
	int	size;
	int	type;

	size = str_arr_size(str);

	i = 0;
	type = 0;
	while (str && str[i])
	{
		type = is_redirection(str[i], 0);
		if (type)
			size--;
		if (str[i + 1] &&
			(type == R_DDIR || type == R_DIR))
			size--;
		if (str[i + 1] &&
			(type == L_DIR || type == L_DDIR))
			size--;
		i++;
	}
	return (size);
}

char	**eliminate_redirections(char **args)
{
	int		size;
	char	**dest;
	int		i;
	int		j;
	int		type;

	i = 0;
	j = 0;
	size = str_arr_size_r(args);
	if (size <= 0)
		return (NULL);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = NULL;
	type = 0;
	while (args && args[i])
	{
		
		type = is_redirection(args[i], 0);
		if (type)
			if (args[i])
			{
				i++;
				if (args[i])
					i++;
			}

		if (args[i])
		{
			dest[j] = ft_strdup(args[i]);
			j++;
		}
		if (!args[i])
			break ;
		i++;
	}
	str_arr_free(args);
	return (dest);
}

int	setup_rfiles(t_cmd	*arg, int type, int i, char **envr, t_data *data)
{
	char	*work_path;
	char	*final_path;

	//if (!arg->args[i + 1])
	//	return (printf("minishell:syntax error near unexpected token`newline'\n"));
	work_path = pwd(data);
	final_path = concat_path(work_path, arg->args[i + 1]);
	if (type == R_DIR)
		arg->fout = open(final_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (type == R_DDIR)
		arg->fout = open(final_path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (type == L_DIR)
		arg->fin = open(final_path, O_RDONLY);
	if (type == L_DDIR)
		arg->fin = here_doc(arg->args[i + 1], 1, envr);
	str_arr_display(arg->args);

	//printf("args[i] %s fin = %d fout = %d\n", arg->args[i], arg->fin, arg->fout);
	free(final_path);	
	return (1);
}

int	open_redirections(t_data *data)
{
	int		i;
	t_cmd	*arg;
	t_list	*tmp;
	int		type;

	tmp = data->cmd;
	while (tmp)
	{
		type = 0;
		arg = tmp->content;
		i = 0;
		while (arg->args && arg->args[i])
		{
			type = is_redirection(arg->args[i], 0);
			if (type)
			{
				setup_rfiles(arg, type, i, data->env_str, data);
				i++;
			}
			if (arg->args[i])
				i++;
		}
		arg->args = eliminate_redirections(arg->args);

		if (arg->args)
			arg->name = ft_strdup(arg->args[0]);
		tmp = tmp->next;
	}
	return (1);
}

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
