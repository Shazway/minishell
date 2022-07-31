/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:09:48 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/31 14:34:22 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (termios_setup(data) || msh_init(data))
	{
		msh_free(data);
		exit(FAILED_ALLOC);
	}
	minishell_sh(data);
	if (!data->input)
		ft_printf("exit\n");
	msh_free(data);
	return (0);
}
