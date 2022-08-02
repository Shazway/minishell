/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:38:29 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/08/01 21:19:01 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	s1_end;
	size_t	len_src;

	i = 0;
	len_src = ft_strlen(src);
	while (dest && dest[i] && i < size)
		i++;
	s1_end = i;
	if (size == 0)
		return (s1_end + len_src);
	while (src && src[i - s1_end] && i < size - 1)
	{
		dest[i] = src[i - s1_end];
		i++;
	}
	if (dest && s1_end < size)
		dest[i] = '\0';
	return (s1_end + len_src);
}

size_t	ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dest && dest[i])
		i++;
	j = 0;
	while (dest && src && src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (dest)
		dest[i] = '\0';
	return (i);
}