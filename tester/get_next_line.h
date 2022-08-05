/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:26:19 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/31 22:47:59 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define BFZ 512

typedef struct		s_fdlist
{
	char			*buf;
	int				fd;
	struct s_fdlist	*next;
}					t_fdlist;

int					get_next_line(int fd, char **line);
int					ft_strallocat(char **dest, char *src);
char				*rep_newl_zero(char *s);
void				ft_strncpy(char *dest, const char *src, size_t n);
size_t				ft_strlen(const char *s);
t_fdlist			*ft_lstnew(int fd);
void				ft_lstadd_front(t_fdlist **alst, t_fdlist *new);
t_fdlist			*ft_lstfind(t_fdlist *alst, int fd);
void				ft_lstdelete(t_fdlist **alst, int fd);

#endif
