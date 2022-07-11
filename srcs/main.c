/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:09:48 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/11 15:45:39 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data					*data;
	extern struct sigaction	g_signals;
	int						ret;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (termios_setup(data))
	{
		free(data);
		return (1);
	}
	g_signals.sa_sigaction = sig_info;
	if (msh_init(data))
		return (1);
	ret = prompt_loop(data);
	if (!data->input)
		printf("exit\n"));
	clear_history();
	free(data);
	return (0);
}
