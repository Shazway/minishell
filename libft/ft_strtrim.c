/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:39:03 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/06/04 19:02:55 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include <string.h>

static void	strtrim_worker(size_t slen, size_t *k, size_t *i, size_t *len)
{
	if (slen == 0)
		*k = (*i)++;
	else
		*k = slen - 1;
	if (*i > *k)
		*len = 0;
	else if (*i == *k)
		*len = 1;
}

/*
** Trim set of characters from the beginning
** and the end of a string, and return the new string.
** Use $i index to walk from start to end
** while it find the $set characters to trim.
** Calculate length of $s1 :
** if it's equal to 0, $k is affected by $i
** and $i is incremented to get $i > $k,
** else, affect $k by $slen - 1, to point on the
** last character
** if $i > $k then $len = 0
** else if $i == $k, that means we got one character
** in $s1,
** else if $i < $k :
** using $k, it will move from right to left while
** it find the trimmable characters,
** $len = $k - $i + 1, to get the length of the string
** in the middle.
** Allocate $result of size $len
** copy $len characters from $i (from $i to $k)
** return $result
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	i;
	size_t	k;
	size_t	len;
	size_t	slen;

	if (!s1)
		return (NULL);
	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	slen = ft_strlen(s1);
	strtrim_worker(slen, &k, &i, &len);
	if (i < k)
	{
		while (ft_strchr(set, s1[k]) && k >= 0)
			k--;
		len = k - i + 1;
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + i, len + 1);
	return (result);
}
