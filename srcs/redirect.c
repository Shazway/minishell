/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:13:47 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/15 21:47:56 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char const *s, char *set)
{
	int	i;
	int	n;
	int	upto;
	int	from;

	i = 0;
	n = 0;
	from = 0;
	while (s[i])
	{
		while (s[i] && !ft_strchr(set, s[i]))
			i++;
		upto = i;
		while (s[i] && ft_strchr(set, s[i]))
			i++;
		if (upto > from)
			n++;
		from = i;
	}
	return (n);
}


void	magic_parser(t_data *data)
{
	int	i;
    int dq_state;
    int sq_state;
    int cmd_state;
    int arg_state;
    t_list  *cur_cmd;
    t_cmd   *cmd_content;

    dq_state = 0;
    sq_state = 0;
    cmd_state = 1;
    arg_state = 0;
    cur_cmd = data->cmd;
	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '>')
		{
            i++;
            if (data->input[i] == '>')

			while (data->input[i])
			{
				i++;
			}
		}
        else if (data->input[i] == '<')
        {
            i++;
            if (data->input[i] == '<')
        }
        else if (data->input[i] == '|')
        {

        }
        else if (data->input[i] != '|' && data->input[i] != '>' && data->input != '<')
        {
            if (cmd_state == 1)
            {

            }
            else if (arg_state == 1)
            {

            }
        }
		i++;
	}
}