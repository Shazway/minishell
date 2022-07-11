/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:28:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/11 02:16:50 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_exit(int ac, char **av)
{
	if (ac != 2)
		return(printf("bash: exit: too many arguments\n"));
	exit(error);
}
