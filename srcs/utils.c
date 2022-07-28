/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:55:18 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/29 00:00:00 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free(void	*ptr)
{
	free(ptr);
	return (NULL);
}

char	**str_arr_free(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

void	*ft_free_ptrs(void **p1, void **p2, void **p3, void **p4)
{
	if (p1 && *p1)
		*p1 = ft_free(*p1);
	if (p2 && *p2)
		*p2 = ft_free(*p2);
	if (p3 && *p3)
		*p3 = ft_free(*p3);
	if (p4 && *p4)
		*p4 = ft_free(*p4);
	return (NULL);
}

void	*ft_free_sars(char ***sar1, char ***sar2, char ***sar3, char ***sar4)
{
	if (sar1 && *sar1)
		*sar1 = str_arr_free(*sar1);
	if (sar2 && *sar2)
		*sar2 = str_arr_free(*sar2);
	if (sar3 && *sar3)
		*sar3 = str_arr_free(*sar3);
	if (sar4 && *sar4)
		*sar4 = str_arr_free(*sar4);
	return (NULL);
}

int	ft_malloc(void **p, size_t length)
{
	*p = malloc(length);
	if (*p)
		return (1);
	return (0);
}
