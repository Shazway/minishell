/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 00:21:17 by telli             #+#    #+#             */
/*   Updated: 2022/02/05 16:54:38 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cast_dst;
	unsigned char	*cast_src;

	cast_dst = (unsigned char *)dest;
	cast_src = (unsigned char *)src;
	if (!n || dest == src)
		return (dest);
	while (n)
	{
		*cast_dst++ = *cast_src++;
		n--;
	}
	return (dest);
}
