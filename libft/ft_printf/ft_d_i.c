/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_i.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:32:58 by tmoragli          #+#    #+#             */
/*   Updated: 2022/05/05 01:16:47 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_d(t_parsing *parsing, int nb)
{
	(void)parsing;
	if (nb == -2147483648)
	{
		ft_s(parsing, "-2147483648");
		return ;
	}
	if (nb == 0)
	{
		write(1, "0", 1);
		parsing->count++;
		return ;
	}
	if (nb < 0)
		parsing->count++;
	parsing->count++;
	ft_putnbr_base(nb, "0123456789", parsing);
}
