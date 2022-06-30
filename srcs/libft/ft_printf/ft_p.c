/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 23:55:50 by tmoragli          #+#    #+#             */
/*   Updated: 2022/05/05 01:16:47 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_p(t_parsing *parsing, long unsigned int p)
{
	write(1, "0", 1);
	write(1, "x", 1);
	if (p == 0)
	{
		write(1, "0", 1);
		parsing->count += 3;
		return ;
	}
	parsing->count += 3;
	ft_putnbr_base_2(p, "0123456789abcdef", parsing);
	parsing->type = 0;
}
