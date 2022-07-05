/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:37:52 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/05/30 18:37:53 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** 1- If the number is negative,
** it write '-' in $fd.
** 2- If the number is bigger than 10
** or smaller than -10 :
** 3- Dividing $nb by 10, if $div is negative
** multiply it by -1.
** 4- Calling the funcion again, with $div as input
** 5- Read comment from (1) with 129 as example
** that will make multiple instance of ft_putnbr_fd.
** 6- When a ft_putnbr_fd() instance get a number < 10 and > -10
** it will write it in $fd by doing (7)
** 7- Doing a modulo 10 for $nb in $c,
** if c < 0, make it positive, then convert to ascii and
** call ft_putchar_fd()
** 8- Other instances continue to execute their code doing (7)
** , from last called to first called.
*/

void	ft_putnbr_fd(int nb, int fd)
{
	char	c;
	int		div;

	if (nb < 0)
		ft_putchar_fd('-', fd);
	if (!(nb < 10 && nb > -10))
	{
		div = nb / 10;
		if (div < 0)
			div *= -1;
		ft_putnbr_fd(div, fd);
	}
	c = nb % 10;
	if (c < 0)
		c *= -1;
	c += '0';
	ft_putchar_fd(c, fd);
}
