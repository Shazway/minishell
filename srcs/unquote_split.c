/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:04:51 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/10 20:15:42 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quote(char *type, char c)
{
	if (*type == -1 && (c == '"' || c == '\''))
		*type = c;
	else if (c == *type)
		*type = -1;
}

int	count_words(char *s, char c)
{
	int	i;
	int	count;
	char type;

	count = 1;
	i = 0;
	type = -1;
	if (c == '|')
		s = ft_strtrim(s, "|");
	else if (c == ' ')
		s = ft_strtrim(s, " ");
	while (s[i])
	{
		check_quote(&type, s[i]);
		if ((s[i] == c && type == -1))
		{
			count++;
			while (s[i] && s[i] == c)
				i++;
		}
		else
			i++;
	}
	free(s);
	return (count);
}

int	malloc_words(char *s, char c, char **str, int count)
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
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && (s[i] != c || type != -1))
		{
			check_quote(&type, s[i]);
			j++;
			i++;
		}
		if (!ft_malloc((void **)&str[k], sizeof(char) * (j + 1)))
			return (1);
		k++;
	}
	return (0);
}

char	**fill(char *s, char c, char **str)
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
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && (s[i] != c || type != -1))
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

char	**unquote_split(char *s, char c)
{
	char	**str;
	char	**tmp;
	int		count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	printf("%d\n", count);
	if (!ft_malloc((void **)&str, sizeof(char *) * (count + 1)))
		return (NULL);
	str[count] = NULL;
	if (malloc_words(s, c, str, count))
		return (NULL);
	tmp = fill(s, c, str);
	int i = 0;
	while (tmp && tmp[i])
	{
		printf("Temp = [%s]\n", tmp[i]);
		i++;
	}
	printf("Temp = [%s]\n", tmp[i]);
	return (tmp);
}
