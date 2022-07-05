/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:35:46 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/06/04 17:36:08 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** allocate num * size using malloc
** then using ft_bzero to intiate all
** bytes to 0
*/

void	*ft_calloc(size_t num, size_t size)
{
	void	*m;

	m = malloc(num * size);
	if (!m)
		return (NULL);
	ft_bzero(m, num * size);
	return (m);
}
