/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:38:54 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/26 15:36:02 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	f;

	if (!(*s2) || !s2)
		return ((char *)s1);
	i = 0;
	j = 0;
	while ((i < n || n == 0) && s1[i])
	{
		f = i;
		if (s1[i] != s2[j])
			i++;
		else
			while (s1[i] == s2[j] && s1[i] && s2[j++] && (i++ < n || n == 0))
				;
		if (s2[j] == '\0')
			return ((char *)&s1[f]);
		else
			j = 0;
	}
	return (NULL);
}
