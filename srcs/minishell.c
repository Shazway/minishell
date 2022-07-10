/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/11 00:38:46 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    msh_init(t_data *data)
{
    if (set_env(data))
        return (1);
    data->cmd = NULL;
    return (0);
}

int    msh_free(t_data *data)
{
    if (data->cmd)
        free(data->cmd);
    return (1);
}

void	prompt_loop(t_data *data)
{
	if (signal_intercept())
		exit(1);
	data->input = readline("\033[1;32m""➜ ""\033[1;36m"" minishell ""\033[0m");
	if (!data->input)
		exit(printf("exit\n"));
	if (!(data->input[0] == 0))
	{
		printf("%s\n", data->input);
		add_history(data->input);
		parsing(data);
	}
	free(data->input);
}
