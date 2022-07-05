/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 02:40:39 by telli             #+#    #+#             */
/*   Updated: 2022/02/05 17:00:51 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

void	ft_malloc_words(char const *s, char c, char **str, int count)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	while (k < count)
	{
		j = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			j++;
			i++;
		}
		if (!ft_malloc((void **)&str[k], sizeof(char) * (j + 1)))
			return ;
		k++;
	}
}

char	**ft_fill(char const *s, char c, char **str)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	while (s[i] && str[k])
	{
		j = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			str[k][j] = s[i];
			i++;
			j++;
		}
		str[k][j] = '\0';
		k++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	if (!ft_malloc((void **)&str, sizeof(char *) * (count + 1)))
		return (NULL);
	str[count] = NULL;
	ft_malloc_words(s, c, str, count);
	return (ft_fill(s, c, str));
}
