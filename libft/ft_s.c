/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 23:55:47 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/25 22:28:01 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_s(t_parsing *parsing, char *s)
{
	if (!s)
	{
		write(1, "(null)", 6);
		parsing->count += 6;
		return ;
	}
	else
		ft_printarray(s, parsing);
}
