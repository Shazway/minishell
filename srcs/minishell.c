/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/28 01:51:29 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prompt_string(t_data *data)
{
	char	*tmp;
	char	*current_folder;
	char	*crf_dolar;

	current_folder = NULL;
	crf_dolar = NULL;
	tmp = NULL;
	current_folder = ft_strrchr(data->relative_path, '/');
	if (ft_strlen(current_folder) == 1)
		crf_dolar = ft_strjoin(current_folder,
				"\001 ▶\002 \001\033[1;34m\002""\001\033[0m\002");
	else
		crf_dolar = ft_strjoin(current_folder + 1,
				"\001 ▶\002 \001\033[1;34m\002""\001\033[0m\002");
	if (!crf_dolar)
		msh_exit(data);
	tmp = data->prompt;
	data->prompt = ft_strjoin("\001\033[1;32m\002""╔\002"
			"\001\033[1;32m\002"" minishell" " " "\001╝\002" " " "\001\033[1;31m\002""",
			crf_dolar);
	if (!data->prompt)
		msh_exit(data);
	free(crf_dolar);
	free(tmp);
}



void	ministart(t_data *data)
{
	if (!is_opened_quotes(data) || !check_input(data))
	{
		ft_printf("%s", data->error_msh);
		return ;
	}
	add_history(data->input);
	if (ft_strchr(data->input, '$'))
		data->input = expand_variables(data, data->input);
	if (parsing(data))
	{
		delete_quotes(data);
		open_redirections(data);
		search_cmds(data);
		execute(data);
		free_pipes(data);
		ft_lstclear(&data->cmd, &free_cmd);
	}
}

void	minishell_sh(t_data *data)
{
	while (1)
	{
		if (signal_intercept())
			exit(1);
		set_prompt_string(data);
		data->input = readline(data->prompt);
		if (!data->input)
			break ;
		else
			ministart(data);
		free(data->input);
	}
}
