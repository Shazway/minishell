/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:21 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/20 17:22:43 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_data *data, int ac, char **av)
{
	char *path;

	(void)ac;
	(void)av;
	path = get_pwd(data);
	printf("%s\n", path);
	free(path);
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
