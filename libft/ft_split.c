/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:38:06 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/06/04 18:50:00 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocate the proper size of $dest
** copying from $src beginning with $from index
** up to $upto that means excluding the character in $upto index
** null terminate, and return $dest.
*/

static char	*ft_strallocpy(char const *src, int from, int upto)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (upto - from) + 1);
	if (!dest)
		return (NULL);
	dest = ft_memcpy(dest, src + from, upto - from);
	dest[upto - from] = '\0';
	return (dest);
}

/*
** Count and return the number of strings
** separated by $c in $s.
** Initiate $from with 0.
** That function have 3 loops :
** The First loop, end when it reach \0,
** two loops inside the first loop.
** The second loop continue moving if
** it don't find the separator and \0
** $upto store the index of the first separator
** found after normal characters.
** The third loop continue moving if
** it don't find a normal character and \0
** If $upto > $from that means we found
** a string that have at least one character
** that means we can increment $n
** $from store the index of the normal
** character after separators.
** return $n.
*/

static int	count_stabsize(char const *s, char c)
{
	int	i;
	int	n;
	int	upto;
	int	from;

	i = 0;
	n = 0;
	from = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		upto = i;
		while (s[i] == c && s[i])
			i++;
		if (upto > from)
			n++;
		from = i;
	}
	return (n);
}

/*
** The same as count_stabsize()
** But instead of counting
** it copy to the tab of string
** using ft_strallocpy();
** $k is used to index the tab of strings
** return the tab of strings
** If allocation fail, $n = -1
*/

static char	**splitstotab(char const *s, char c, char **stab, int *n)
{
	int	i;
	int	k;
	int	upto;
	int	from;

	i = 0;
	k = 0;
	from = 0;
	while (s[i])
	{
		split_worker(s, &i, &upto, c);
		if (upto > from)
		{
			stab[k] = ft_strallocpy(s, from, upto);
			if (!stab[k++])
			{
				*n = -1;
				break ;
			}
		}
		from = i;
	}
	return (stab);
}

/*
** Free strings then free the tab of these strings
*/

static void	stabfree(char ***stab, int stabsize)
{
	int		i;
	char	**sarray;

	sarray = *stab;
	i = -1;
	while (++i < stabsize)
		free(sarray[i]);
	free(sarray);
	*stab = NULL;
}

/*
** Split $s into a tab of strings separated
** by c
** First count the number of sub-strings
** then allocate the tab for strings, + 1 to NULL terminate
** Call splitstotab() to extract sub-strings from
** $s to $stab
** If $n is affected by -1 after splitstotab()
** free everything and return NULL.
** If not, NULL terminate the tab by affecting the last case.
*/

char	**ft_split(char const *s, char c)
{
	int		stabsize;
	int		n;
	char	**stab;

	if (!s)
		return (NULL);
	n = count_stabsize(s, c);
	stabsize = n;
	stab = (char **)malloc(sizeof(char *) * (stabsize + 1));
	if (!stab)
		return (NULL);
	stab = splitstotab(s, c, stab, &n);
	if (n == -1)
	{
		stabfree(&stab, stabsize);
		return (NULL);
	}
	stab[stabsize] = NULL;
	return (stab);
}
