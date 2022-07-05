/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:39:08 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/05/30 18:39:09 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	size_t	realen;
	char	*xtr;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		realen = 0;
	else if (len > slen - start)
		realen = slen - start;
	else
		realen = len;
	xtr = malloc(sizeof(char) * (realen + 1));
	if (!xtr)
		return (NULL);
	if (realen)
		ft_memcpy(xtr, s + start, realen);
	xtr[realen] = '\0';
	return (xtr);
}
