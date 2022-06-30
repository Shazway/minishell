/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:20:50 by tmoragli          #+#    #+#             */
/*   Updated: 2022/02/05 16:35:33 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	temp2 = *lst;
	while (temp2)
	{
		temp = temp2->next;
		if (del)
			del(temp2->content);
		free(temp2);
		temp2 = temp;
	}
	*lst = NULL;
}
