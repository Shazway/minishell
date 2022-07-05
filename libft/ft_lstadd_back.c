/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:36:26 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/06/04 17:59:58 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** If the list is empty,
** call ft_lstadd_front(),
** else, call call ft_lstlast()
** then link it with the the new element
*/

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*p;

	if (!alst || !new)
		return ;
	if (!*alst)
		ft_lstadd_front(alst, new);
	else
	{
		p = ft_lstlast(*alst);
		p->next = new;
		p->next->next = NULL;
	}
}
