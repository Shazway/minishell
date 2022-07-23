/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:21 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/23 14:49:26 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_data *data, int ac, char **av)
{
	(void)ac;
	(void)av;
	if (!data->relative_path)
		return (-1);
	printf("%s\n", data->relative_path);
	return (0);
}
