/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:56 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/24 00:16:55 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset(t_data *data, int ac, char **av)
{
    int     i;
    char    **to_del;
    int     len;
    int     j;
    char    **old_envr;
    
    len = 0;
    j = 0;
    to_del = malloc(ac * sizeof(char *));
    i = 1;
    while (av && av[i])
    {
        if (is_validid(av[i], ft_strlen(av[i])))
        {
            to_del[j] = ft_strdup(av[i]);
            j++;
        }
        i++;
    }
     to_del[j] = NULL;
    old_envr = data->env_str;
    data->env_str = str_arr_del(data->env_str, to_del, j);
    str_arr_free(old_envr);
    return (1);
}