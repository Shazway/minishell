/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:59:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/16 23:55:54 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char	*str, int *type)
{
	if (!str || (str && (str[0] == '"' || str[0] == 39)))
		return (*type);
	if (!ft_strncmp(str, ">", 2))
		*type = R_DIR;
	if (!ft_strncmp(str, ">>", 3))
		*type = R_DDIR;
	if (!ft_strncmp(str, "<", 2))
		*type = L_DIR;
	if (!ft_strncmp(str, "<<", 3))
		*type = L_DDIR;
	return (*type);
}

int	str_arr_size_r(char	**str)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (str && str[i])
	{
		if (!is_redirection(str[i], 0))
			size++;
		i++;
	}
	return (size);
}
void	str_arr_display(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		printf("Args[%d] = [%s]\n", i, str[i]);
		i++;
	}
}


char	**eliminate_redirections(char **args)
{
	int		size;
	char	**dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = str_arr_size_r(args);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = NULL;
	while (args && args[i])
	{
		if (is_redirection(args[i], 0))
			i++;
		if (!args[i])
			break ;
		else
			dest[j] = ft_strdup(args[i]);
		j++;
		i++;
	}
	str_arr_free(args);
	str_arr_display(args);
	return (dest);
}

void	create_file(char *path)
{
	int	temp_fd;

	temp_fd = open(path, O_CREAT, S_IRUSR, S_IWUSR);
	if (temp_fd != -1)
		close(temp_fd);
}

int	setup_rfiles(t_cmd	*arg, int *type, int i)
{
	char	*work_path;
	char	*final_path;

	if (!arg->args[i + 1])
		return (printf("minishell:syntax error near unexpected token`newline'\n"));
	work_path = pwd();
	if (*type == R_DIR || *type == R_DDIR)
		final_path = concat_path(work_path, arg->args[i + 1]);
	else
	{
		if (i != 0)
			final_path = concat_path(work_path, arg->args[i - 1]);
		arg->fout = 1;
		return (1);
	}
	create_file(final_path);
	if (*type == R_DIR)
		arg->fin = open(final_path, O_TRUNC, O_WRONLY);
	if (*type == R_DDIR)
		arg->fin = open(final_path, O_APPEND, O_WRONLY);
	if (*type == L_DIR)
		arg->fout = open(final_path, O_APPEND, O_WRONLY);
//	if (*type == L_DDIR)
//		here_docs()
	//args = eliminate_redirections(args);
	printf("fin = %d fout = %d\n", arg->fin, arg->fout);
	free(final_path);
	return (1);
}

int	open_redirections(t_data *data)
{
	int		i;
	t_cmd	*arg;
	t_list	*tmp;
	int		type;

	i = 0;
	tmp = data->cmd;
	while (data->cmd)
	{
		type = 0;
		arg = data->cmd->content;
		while (arg->args && arg->args[i])
		{
			if (is_redirection(arg->args[i], &type))
				setup_rfiles(arg, &type, i);
			i++;
		}
		data->cmd = data->cmd->next;
	}
	data->cmd = tmp;
	return (1);
}

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
		ft_lstadd_back(&(data->cmd), ft_lstnew((void *)temp));
		temp->fin = -1;
		temp->fout = -1;
		split_spaces(temp, pipe_split[i]);
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
	token->cmd = ft_strdup(token->args[0]);
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
