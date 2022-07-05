/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:36:20 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/06/04 17:59:28 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_worker(char *s, int div, int i, int n)
{
	while (div != 0)
	{
		if (n < 0)
			s[i++] = n / -div + '0';
		else
			s[i++] = n / div + '0';
		n = n % div;
		div = div / 10;
	}
	s[i] = '\0';
	return (i);
}

/*
** Calculate the divider and the counter
** then allocate a string that can hold the number
** if the number is negative, write - in the string.
** Extract digit by digit from left to right by dividing
** by div and dividing div by 10 every time to extract the right number
** converting every digit to into ascii then copy it in $s.
*/

char	*ft_itoa(int n)
{
	char	*s;
	int		div;
	int		count;
	int		i;
	int		x;

	div = 1;
	x = n;
	count = 1;
	x = x / 10;
	while (x != 0 && count++ >= 0)
	{
		div *= 10;
		x = x / 10;
	}
	if (n < 0)
		count++;
	s = malloc(sizeof(char) * (count + 1));
	if (!s)
		return (NULL);
	i = 0;
	if (n < 0)
		s[i++] = '-';
	i = itoa_worker(s, div, i, n);
	return (s);
}
