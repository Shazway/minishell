/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:07:43 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/20 15:37:35 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (str[i + 1] && (type == R_DDIR || type == R_DIR))
			size--;
		if (str[i + 1] && (type == L_DIR || type == L_DDIR))
			size--;
		i++;
	}
	return (size);
}

char	**destroy_redirections(char **dest, char **args)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (args && args[i])
	{
		if (is_redirection(args[i], 0))
		{
			if (args[i])
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
	return (dest);
}

char	**eliminate_redirections(char **args)
{
	int		size;
	char	**dest;

	size = str_arr_size_r(args);
	if (size <= 0)
		return (NULL);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = NULL;
	dest = destroy_redirections(dest, args);
	str_arr_free(args);
	return (dest);
}

int	setup_rfiles(t_cmd	*arg, int i, char **envr, t_data *data)
{
	char	*work_path;
	char	*final_path;
	int		type;

	type = is_redirection(arg->args[i], 0);
	work_path = get_pwd(data);
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
	free(final_path);
	return (1);
}

int	open_redirections(t_data *data)
{
	int		i;
	t_cmd	*arg;
	t_list	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		arg = tmp->content;
		i = 0;
		while (arg->args && arg->args[i])
		{
			if (is_redirection(arg->args[i], 0))
			{
				setup_rfiles(arg, i, data->env_str, data);
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
