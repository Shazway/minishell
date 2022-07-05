/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:04:42 by tmoragli          #+#    #+#             */
/*   Updated: 2022/02/05 16:41:37 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newelem;

	newelem = (t_list *)malloc(sizeof(t_list));
	if (!newelem)
		return (NULL);
	newelem->next = NULL;
	newelem->content = content;
	return (newelem);
}
