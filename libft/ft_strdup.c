/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:38:15 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/27 20:54:18 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	size_t	lensrc;

	if (!src)
		return (NULL);
	lensrc = ft_strlen(src);
	dup = malloc(sizeof(char) * (lensrc + 1));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, src, lensrc);
	dup[lensrc] = '\0';
	return (dup);
}

char	*ft_strndup(char *src, size_t n)
{
	char	*dup;
	size_t	lensrc;
	size_t	lendest;

	if (!src)
		return (NULL);
	if (n < 0)
		return (NULL);
	lensrc = ft_strlen(src);
	lendest = n * (lensrc > n) + lensrc * (lensrc <= n);
	dup = malloc(sizeof(char) * (lendest + 1));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, src, lendest);
	dup[lendest] = '\0';
	return (dup);
}
