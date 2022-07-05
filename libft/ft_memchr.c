/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:37:19 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/06/04 18:04:48 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Moving index in a loop up to n,
** stopping when finding c character
** verify after that if index stopped
** before reaching n, if it stopped return
** the address of the character in the string
** using the index variable. If not return NULL.
*/

void	*ft_memchr(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = s;
	i = 0;
	while (i < n && str[i] != (unsigned char)c)
		i++;
	if (i < n)
		return (&str[i]);
	else
		return (NULL);
}
