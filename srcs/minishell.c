/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/04 03:32:51 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

struct sigaction	g_signal;

void	handler()
{
	printf("\n");
	printf("\033[1;32m""➜ ""\033[1;36m"" minishell ""\033[0m");
	return ;
}

char *get_prompt(char *str)
{
	int i;
	int size;
	int j;
	char *dest;

	size = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '/')
			size = 0;
		size++;
		i++;
	}
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = '\0';
	while (i > 0 && i != '/')
		i--;
	j = 0;
	while (str[i] && dest[j])
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	return (dest);
}

void	prompt_loop(t_data *data)
{
	g_signal.sa_handler = handler;
	sigaction(SIGINT, &g_signal, NULL);
	sigaction(SIGQUIT, &g_signal, NULL);
	data->input = readline("\033[1;32m""➜ ""\033[1;36m"" minishell ""\033[0m");
	if (!data->input)
		exit(printf("\n"));
	if (ft_strlen(data->input) > 0)
		printf("%s\n", data->input);
	add_history(data->input);
	parsing(data);
	free(data->input);
}

int	ft_free(t_data *data)
{
	if (data->cmd)
		free(data->cmd);
	if (data->env_lst)
		free(data->env_lst);
	return (1);
}

int	ft_allocate(t_data *data)
{
	data->cmd = NULL;
	data->env_lst = malloc(sizeof(t_env));
	if (!data->env_lst)
		return (ft_free(data));
	return (0);
}

int	main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ft_allocate(data))
		return (1);
	while (1)
		prompt_loop(data);
	clear_history();
	free(data);
	return (0);
}