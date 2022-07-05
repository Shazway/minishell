/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:57:35 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/05 19:49:07 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <signal.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define WORD = 0;
# define R_DIR = 1;
# define L_DIR = 2;
# define RD_DIR = 3;
# define LD_DIR = 4;
# define O_PARENTH = 5;
# define C_PARENTH = 6;
# define AND_OP = 7;
# define OR_OP = 8;
# define PIPE = 9;

typedef struct s_token
{
	char	*str;
	char	**str_split;
	char	*name;
	char	*content;
	char	*redirect;
}	t_token;

typedef struct s_trash
{
	void			*to_free;
	struct s_trash	*next;
}	t_trash;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	int					read_ret;
	char				*buf_trash;
	char				*input;
	char				*output;
	char				**commands;
	char				**env_str;
	t_env				*env_lst;
	t_list				*cmd;
	t_trash				*trash;
	struct sigaction	signals;
}	t_data;

int		ft_echo(int ac, char **av);
int		check_echo_n(char *str);
char	*pwd(void);
int		is_double_dot(char *str);

int		cd(char *str);
char	*path_finder(char *str);
int		directory_exists(char *s);
char	*previous_dir(char *str);

void	handler(void);
int		signal_intercept(t_data *data);
void	prompt_loop(t_data *data);
int		ft_free(t_data *data);
int		ft_allocate(t_data *data);

void	print_result(t_token *token);
void	split_spaces(t_token *token, char *content);
void	del_token(void *content);
int		parsing(t_data *data);

void	ft_free_tab(char **str);

#endif