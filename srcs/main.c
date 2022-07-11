/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:09:48 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/11 16:02:05 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data					data;

	if (termios_setup(data))
	{
		free(data);
		return (1);
	}
	if (msh_init(&data))
		return (1);
	prompt_loop(&data);
	if (data.input)
		printf("exit\n"));
	clear_history();
	msh_free(&data);
	return (0);
}
