/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 23:55:45 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/25 22:24:10 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hex(t_parsing *parsing, unsigned int nb)
{
	if (nb == 0)
	{
		write(1, "0", 1);
		parsing->count++;
		return ;
	}
	parsing->count++;
	if (parsing->type == 'x' && nb > 0)
	{
		ft_putnbr_base_2(nb, "0123456789abcdef", parsing);
		return ;
	}
	if (parsing->type == 'X' && nb > 0)
	{
		ft_putnbr_base_2(nb, "0123456789ABCDEF", parsing);
		return ;
	}
}
