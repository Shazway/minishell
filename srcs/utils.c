/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:55:18 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/29 11:34:06 by mdkhissi         ###   ########.fr       */
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

void	*ft_free_strs(char **s1, char **s2, char **s3, char **s4)
{
	if (s1 && *s1)
		*s1 = ft_free(*s1);
	if (s2 && *s2)
		*s2 = ft_free(*s2);
	if (s3 && *s3)
		*s3 = ft_free(*s3);
	if (s4 && *s4)
		*s4 = ft_free(*s4);
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
