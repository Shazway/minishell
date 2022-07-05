/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:36:38 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/06/04 18:00:28 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Clear the list and free it
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmpnext;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		tmpnext = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = tmpnext;
	}
	*lst = NULL;
}
