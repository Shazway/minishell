/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:09:06 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/31 22:48:52 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Allcoate a new t_fdlist element,
** then copy (fd) and intiatialize,
** (buf) with "".
*/

t_fdlist	*ft_lstnew(int fd)
{
	t_fdlist *new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->buf = malloc(sizeof(char) * (BFZ + 1));
	new->buf[0] = '\0';
	new->fd = fd;
	new->next = NULL;
	return (new);
}

/*
** if the list is empty
** the first pointer is linked to the new,
** if the list was empty, that'all,
** else, save the first element in $tmp,
** make new as first element,
** then $tmp as next element.
*/

void		ft_lstadd_front(t_fdlist **alst, t_fdlist *new)
{
	t_fdlist *tmp;

	if (!alst || !new)
		return ;
	if (!*alst)
		*alst = new;
	else
	{
		tmp = *alst;
		*alst = new;
		new->next = tmp;
	}
}

/*
** Find the element that contain the value
** of fd in the list.
*/

t_fdlist	*ft_lstfind(t_fdlist *alst, int fd)
{
	t_fdlist *i;

	if (!alst)
		return (NULL);
	i = alst;
	while (i != NULL)
	{
		if (fd == i->fd)
			return (i);
		i = i->next;
	}
	return (NULL);
}

/*
** Delete and free the element that contain (fd)
** in the list
*/

void		ft_lstdelete(t_fdlist **alst, int fd)
{
	t_fdlist *cur;
	t_fdlist *prev;

	if (!alst || !*alst)
		return ;
	cur = *alst;
	prev = NULL;
	while (cur != NULL && cur->fd != fd)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur)
	{
		if (prev)
			prev->next = cur->next;
		else
			*alst = cur->next;
		free(cur->buf);
		free(cur);
	}
}
