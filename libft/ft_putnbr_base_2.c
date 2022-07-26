/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 22:36:46 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/25 22:27:46 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

void	ft_putchar2(char c)
{
	write(1, &c, 1);
}

static size_t	check_base(char *base)
{
	int		i;
	int		j;

	i = 0;
	if (base == NULL)
		return (0);
	while (base[i])
	{
		j = 0;
		while (base[j])
		{
			if (base[j] == base[i] && i != j)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base_2(long unsigned int nbr, char *base, t_parsing *parsing)
{
	if (nbr * -1 - 1 == 2147483647 || !(check_base(base)))
		return ;
	if (nbr / ft_strlen(base) > 0)
	{
		ft_putnbr_base_2(nbr / ft_strlen(base), base, parsing);
		parsing->count++;
	}
	if (nbr >= 1)
		ft_putchar2(base[nbr % ft_strlen(base)]);
}
