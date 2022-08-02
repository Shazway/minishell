/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:31:41 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/02 18:44:48 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printchar(char c, t_parsing *parsing)
{	
	write(1, &c, 1);
	parsing->count++;
}

void	ft_printarray(char *str, t_parsing *parsing)
{
	while (str && *str)
	{
		write(1, str, 1);
		str++;
		parsing->count++;
	}
}

int	ft_fill_iarr(int *iarr, int value, int n)
{
	int	i;

	i = 0;
	while (iarr && i < n)
	{
		iarr[i] = value;
		i++;
	}
	return (i);
}
