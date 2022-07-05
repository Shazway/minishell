/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:35:27 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/05/30 18:35:30 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** assign 0 to n bytes of s using ft_memset
*/

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
