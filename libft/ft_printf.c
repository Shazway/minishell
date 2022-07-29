/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:17:11 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/29 20:47:29 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_node(t_parsing *parsing)
{
	if (parsing->type == '%')
	{
		write(1, "%", 1);
		parsing->count++;
	}
	if (parsing->type == 'c')
		ft_printchar(va_arg(parsing->argptr, int), parsing);
	if (parsing->type == 's')
		ft_s(parsing, va_arg(parsing->argptr, char *));
	if (parsing->type == 'p')
		ft_p(parsing, va_arg(parsing->argptr, long unsigned int));
	if (parsing->type == 'd' || parsing->type == 'i')
		ft_d(parsing, va_arg(parsing->argptr, int));
	if (parsing->type == 'u')
		ft_u(parsing, (unsigned int)va_arg(parsing->argptr, unsigned int));
	if ((parsing->type == 'x') || (parsing->type == 'X'))
		ft_hex(parsing, (unsigned int)va_arg(parsing->argptr, unsigned int));
}

int	ft_printf(const char *str, ...)
{
	t_parsing	*parsing;
	int			count;

	parsing = malloc(sizeof(t_parsing));
	if (!parsing)
		return (0);
	parsing->count = 0;
	va_start(parsing->argptr, str);
	while (str && *str)
	{
		if (*str == '%')
		{
			str++;
			ft_parsing((char **)&str, parsing);
			ft_node(parsing);
		}
		else
			ft_printchar(*str, parsing);
		str++;
	}
	count = parsing->count;
	free(parsing);
	return (count);
}
