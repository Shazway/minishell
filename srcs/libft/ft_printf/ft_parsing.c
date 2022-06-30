/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:32:04 by tmoragli          #+#    #+#             */
/*   Updated: 2022/05/05 01:16:47 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_initialize(t_parsing *parsing)
{
	parsing->flag = 0;
	parsing->width = 0;
	parsing->lwidth = 0;
	parsing->precision = 0;
	parsing->lprecision = 0;
	parsing->asterisk = 0;
	parsing->type = 0;
}

void	ft_flag(char **str, t_parsing *parsing)
{
	while (*str && **str && (**str == '-' || **str == '0'))
	{
		if (parsing->flag != '-')
			parsing->flag = **str;
		(*str)++;
	}
}

void	ft_width(char **str, t_parsing *parsing)
{
	if (ft_isdigit(**str))
	{	
		parsing->width = 1;
		parsing->lwidth = ft_atoi(*str);
	}
	while (*str && **str && ft_isdigit(**str))
		(*str)++;
}

void	ft_precision(char **str, t_parsing *parsing)
{
	if (**str == '.')
	{
		parsing->precision = 1;
		(*str)++;
		parsing->lprecision = ft_atoi(*str);
	}
	if (**str == '*')
	{
		parsing->asterisk = 1;
		(*str)++;
		parsing->lprecision = va_arg(parsing->argptr, int);
	}
	while (*str && **str && ft_isdigit(**str))
		(*str)++;
}

void	ft_parsing(char **str, t_parsing *parsing)
{
	ft_initialize(parsing);
	ft_flag(str, parsing);
	ft_width(str, parsing);
	ft_precision(str, parsing);
	parsing->type = **str;
}
