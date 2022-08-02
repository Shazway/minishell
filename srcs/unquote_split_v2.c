/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_split_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:15:36 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/02 23:12:30 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(char c)
{
	if (!c)
		return (0);
	if (c == '|')
		return (1);
	return (0);
}

char	*trim_delim(char *s, int (*delim)(char c))
{
	int		start;
	int		end;

	end = 0;
	start = 0;
	if (!s)
		return (NULL);
	while (s && s[start] && delim(s[start]))
		start++;
	while (s && s[end])
		end++;
	if (!end)
		return (s);
	if (end && !s[end])
		end--;
	while (end > 0 && delim(s[end]))
		end--;
	end++;
	if (start == 0 && end == (int)ft_strlen(s) - 1)
		return (s);
	return (ft_substr(s, start, end - start));
}

int	count_words_v2(char *s, int (*delim)(char c), int trim)
{
	int		i;
	int		count;
	char	type;
	char	*str;

	count = 1;
	type = -1;
	i = 0;
	if (!s)
		return (-1);
	if (trim)
		str = ft_strtrim(s, " \t\r\n\v\f");
	else
		str = ft_strdup(s);
	if (!str)
		return (-1);
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
	free(str);
	return (count);
}

int	malloc_words_v2(char *s, int (*delim)(char c), char **str, int count)
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

char	**fill_v2(char *s, int (*delim)(char c), char **str)
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

char	**unquote_split_v2(char *s, int (*delim)(char c), int trim)
{
	char	**str;
	int		count;

	if (!s)
		return (NULL);
	count = count_words_v2(s, delim, trim);
	if (count == -1)
		return (NULL);
	if (!ft_malloc((void **)&str, sizeof(char *) * (count + 1)))
		return (NULL);
	str[count] = NULL;
	if (malloc_words_v2(s, delim, str, count))
		return (NULL);
	return (fill_v2(s, delim, str));
}
