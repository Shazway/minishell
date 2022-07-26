/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 23:56:58 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/25 22:28:15 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_u(t_parsing *parsing, unsigned int u)
{
	if (u == 0)
	{
		write(1, "0", 1);
		parsing->count++;
		return ;
	}
	parsing->count++;
	ft_putnbr_base_2(u, "0123456789", parsing);
}
