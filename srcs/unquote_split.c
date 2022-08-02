/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:15:36 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/03 00:14:44 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words_worker(char *str, int (*delim)(char c))
{
	int		count;
	int		i;
	char	type;

	type = -1;
	i = 0;
	count = 1;
	while (str[i])
	{
		check_quote(&type, str[i]);
		if ((delim(str[i]) && type == -1))
		{
			count++;
			while (str[i] && delim(str[i]))
				i++;
		}
		else
			i++;
	}
	return (count);
}

int	count_words(char *s, int (*delim)(char c), int trim)
{
	char	*str;
	int		count;

	if (!s)
		return (-1);
	if (trim)
		str = ft_strtrim(s, " \t\r\n\v\f");
	else
		str = ft_strdup(s);
	if (!str)
		return (-1);
	count = count_words_worker(str, delim);
	free(str);
	return (count);
}

int	malloc_words(char *s, int (*delim)(char c), char **str, int count)
{
	int		i;
	int		j;
	int		k;
	char	type;

	i = 0;
	k = 0;
	type = -1;
	while (k < count)
	{
		j = 0;
		while (s[i] && delim(s[i]))
			i++;
		while (s[i] && (!delim(s[i]) || type != -1))
		{
			check_quote(&type, s[i]);
			j++;
			i++;
		}
		if (!ft_malloc((void **)&str[k], sizeof(char) * (j + 1)))
			return (str_arr_free(str) == 0);
		k++;
	}
	return (0);
}

char	**fill(char *s, int (*delim)(char c), char **str)
{
	int		i;
	int		k;
	int		j;
	char	type;

	i = 0;
	type = -1;
	k = 0;
	while (s[i] && str[k])
	{
		j = 0;
		while (s[i] && delim(s[i]))
			i++;
		while (s[i] && (!delim(s[i]) || type != -1))
		{
			check_quote(&type, s[i]);
			str[k][j] = s[i];
			j++;
			i++;
		}
		str[k][j] = '\0';
		k++;
	}
	return (str);
}

char	**unquote_split(char *s, int (*delim)(char c), int trim)
{
	char	**str;
	int		count;

	if (!s)
		return (NULL);
	count = count_words(s, delim, trim);
	if (count == -1)
		return (NULL);
	if (!ft_malloc((void **)&str, sizeof(char *) * (count + 1)))
		return (NULL);
	str[count] = NULL;
	if (malloc_words(s, delim, str, count))
		return (NULL);
	return (fill(s, delim, str));
}
