/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:09:48 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/08/03 02:16:18 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)av;
	(void)ac;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (msh_init(data, env) || termios_setup(data))
	{
		msh_free(data);
		return (1);
	}
	minishell_sh(data);
	if (!data->input)
		ft_printf("exit\n");
	msh_free(data);
	return (0);
}
