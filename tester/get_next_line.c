/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:54:28 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/31 22:47:02 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Bonus version of get_next_line() :
** it manage multiple (fd) by using linked list.
**
** I use static (listf) pointer,
** this help to keep the list alive,
** so as to keep data left in buffer.
**
** First, if the (fd) value is used before,
** we use it, else we create new element.
**
** After that I use the same logic as
** basic GNL, just I changed the functions,
** of libft to save some lines of code.
** What is added and added in the case of read(),
** return 0 or -1, or some error with malloc(),
** or there is no character left, to use for next
** call, that means if (new) is NULL :
**
** Delete the current element that have
** that wrong fd.
*/

int		get_next_line(int fd, char **line)
{
	static t_fdlist	*listf = NULL;
	ssize_t			ret;
	char			*new;
	t_fdlist		*cur;

	if (!(cur = (ft_lstfind(listf, fd))))
		ft_lstadd_front(&listf, (cur = ft_lstnew(fd)));
	(!line) ? ft_lstdelete(&listf, fd) : (void)listf;
	if (!line || !cur)
		return (-1);
	*line = NULL;
	while (1)
	{
		new = rep_newl_zero(cur->buf);
		ret = (ft_strallocat(line, cur->buf)) ? (1) : (-1);
		if (new || ret == -1 || (ret = (read(fd, cur->buf, BFZ))) <= 0)
			break ;
		cur->buf[ret] = '\0';
	}
	(ret == -1) ? (free(*line)) : ((void)*line);
	(ret == -1) ? (*line = NULL) : ((void)*line);
	(ret <= 0) ? (ft_lstdelete(&listf, fd)) : ((void)listf);
	(ret > 0 && new) ? (ft_strncpy(cur->buf, new + 1, 0)) : ((void)ret);
	(!new) ? ft_lstdelete(&listf, fd) : (void)listf;
	return ((ret > 0) ? 1 : ret);
}

/*
** ft_strallocat() is like ft_strjoin()
** just some modifications :
**
** It get the address of (dest) string,
** instead of using return (dest).
**
** If (*dest) or (src) are NULL,
** it will still continue.
**
** It will free (*dest) if it's not NULL.
**
** then it will affect it with the new
** allocated string.
*/

int		ft_strallocat(char **dest, char *src)
{
	size_t	lendest;
	size_t	lensrc;
	char	*result;

	if (!*dest && !src)
		return (0);
	lendest = ft_strlen(*dest);
	lensrc = ft_strlen(src);
	result = malloc(sizeof(char) * (lendest + lensrc + 1));
	if (!result)
		return (0);
	ft_strncpy(result, *dest, 0);
	ft_strncpy(result + lendest, src, 0);
	if (*dest != NULL || dest != NULL)
		free(*dest);
	*dest = result;
	return (1);
}

/*
** This function search for '\n',
** and replace it by '\0'.
*/

char	*rep_newl_zero(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] != '\0')
	{
		s[i] = '\0';
		return ((char *)&s[i]);
	}
	return (NULL);
}

/*
** Copy (src) string to (dest)
*/

void	ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	if (!dest || !src || n < 0)
		return ;
	i = -1;
	if (n == 0)
	{
		while (src[++i])
			dest[i] = src[i];
		dest[i] = '\0';
	}
	else
	{
		while (src[++i] && i < n)
			dest[i] = src[i];
		dest[n] = '\0';
	}
}

/*
** Count the length of string
*/

size_t	ft_strlen(const char *s)
{
	size_t l;

	l = 0;
	while (s && s[l] != '\0')
		l++;
	return (l);
}
