/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:38:15 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/17 23:47:52 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	size_t	lensrc;

	lensrc = ft_strlen(src);
	if (!lensrc)
		return (NULL);
	dup = malloc(sizeof(char) * (lensrc + 1));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, src, lensrc);
	dup[lensrc] = '\0';
	return (dup);
}
