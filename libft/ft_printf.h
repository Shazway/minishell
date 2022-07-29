/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:03:56 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/29 20:47:42 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include "libft.h"

typedef struct s_parsing
{
	char	flag;
	int		width;
	int		lwidth;
	char	precision;
	char	asterisk;
	int		lprecision;
	char	type;
	int		count;
	va_list	argptr;
}					t_parsing;

int		ft_printf(const char *str, ...);
void	ft_parsing(char **str, t_parsing *parsing);
void	ft_putnbr_base(int nbr, char *base, t_parsing *parsing);
void	ft_putnbr_base_2(long unsigned int nbr, char *base, t_parsing *parsing);
void	ft_s(t_parsing *parsing, char *s);
void	ft_d(t_parsing *parsing, int nb);
void	ft_hex(t_parsing *parsing, unsigned int nb);
void	ft_p(t_parsing *parsing, long unsigned int p);
void	ft_u(t_parsing *parsing, unsigned int u);
void	ft_printarray(char *str, t_parsing *parsing);
void	ft_printchar(char c, t_parsing *parsing);

#endif
