/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:02:08 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/05 19:51:07 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    signal_intercept(t_data *data)
{
    if (sigaction(SIGINT, &(data->signals), NULL) == -1)
        return (1);
    if (sigaction(SIGQUIT, &(data->signals), NULL) == -1)
        return (1);
    return (0);
}

void    prompt_loop(t_data *data)
{
    if (signal_intercept(data))
        exit(1);
    data->input = readline("\033[1;32m""➜ ""\033[1;36m"" minishell ""\033[0m");
    if (!data->input)
        exit(printf("\n"));
    if (ft_strlen(data->input) > 0)
        printf("%s\n", data->input);
    add_history(data->input);
    parsing(data);
    free(data->input);
}

int    ft_free(t_data *data)
{
    if (data->cmd)
        free(data->cmd);
    if (data->env_lst)
        free(data->env_lst);
    return (1);
}

int    ft_allocate(t_data *data)
{
    data->cmd = NULL;
    data->env_lst = malloc(sizeof(t_env));
    if (!data->env_lst)
        return (ft_free(data));
    return (0);
}

void    sig_info(int signal, siginfo_t *s, void *trash)
{
    (void)trash;
    (void)s;
    if (signal == SIGINT)
    {
        printf("\n");
        printf("\033[1;32m""➜ ""\033[1;36m"" minishell ""\033[0m");
    }
    if (signal == SIGQUIT)
        return ;
}
