/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:21 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/20 18:32:32 by tmoragli         ###   ########.fr       */
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

char	*get_pwd(t_data *data)
{
	char	*path;

	path = get_var("PWD", data);
	if (!path)
		return (NULL);
	return (path);
}
