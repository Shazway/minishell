/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:21 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/20 17:09:33 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_data *data)
{
	char	*path;

	path = get_var("PWD", data);
	if (!path)
		return (-1);
	printf("%s\n", path);
	free(path);
	return (0);
}
