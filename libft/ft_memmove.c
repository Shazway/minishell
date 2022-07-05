/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:37:32 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/05/30 18:37:34 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

/*
** If $s is in the left of $d,
** there could be an overlapping,
** so the function copy from the last,
** character to the first,
** if $d is in the left, using ft_memcpy()
** if they are equal, do nothing,
** and return $dest.
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	if (!dest && !src)
		return (NULL);
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (s < d)
		while (n-- > 0)
			d[n] = s[n];
	else if (s > d)
		ft_memcpy(dest, src, n);
	return (dest);
}
