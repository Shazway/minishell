/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:26:23 by telli             #+#    #+#             */
/*   Updated: 2021/01/27 15:59:30 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (*s1 && ft_strchr(set, s1[i]))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	dest = ft_substr(s1, 0, i + 1);
	return (dest);
}
