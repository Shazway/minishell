/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:38:15 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/05/30 18:38:16 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	size_t	lensrc;

	lensrc = ft_strlen(src);
	dup = malloc(sizeof(char) * (lensrc + 1));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, src, lensrc);
	dup[lensrc] = '\0';
	return (dup);
}
