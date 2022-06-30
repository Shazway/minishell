/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/30 17:58:43 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	init_data(t_data *data)
{
	data->nb_pipes = 0;
}

void	prompt_loop(t_data *data)
{
	data->entry = readline("\033[1;32m""➜ ""\033[1;36m"" minishell ""\033[0m");
	if (ft_strlen(data->entry) > 0)
		printf("%s\n", data->entry);
	add_history(data->entry);
	parsing(data);
	printf("Number of pipes is %d\n", data->nb_pipes);
	data->nb_pipes = 0;
	free(data->entry);
}

int	main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_data(data);
	while (1)
		prompt_loop(data);
	clear_history();
	free(data);
	return (0);
}