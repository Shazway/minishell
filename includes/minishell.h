/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:57:35 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/11 00:40:22 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <readline/history.h>
# include <term.h>
# include <signal.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
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

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	int		ac;
	/*> O_RDWR, O_CREAT, O_TRUNC
	>> O_RDWR, O_CREAT, O_APPEND
	< O_RDONLY
	<< */
}	t_cmd;

typedef struct s_data
{
	int					read_ret;
	char				*buf_trash;
	char				*input;
	char				*output;
	char				**commands;
	char				**env_str;
	struct termios		termios;
	t_list				*cmd;
}	t_data;

void	sig_info(int signal, siginfo_t *s, void *trash);
int		ft_echo(int ac, char **av);
int		check_echo_n(char *str);
char	*pwd(void);
int		is_double_dot(char *str);

int		cd(char *str);
char	*path_finder(char *str);
int		directory_exists(char *s);
char	*previous_dir(char *str);

int		signal_intercept(void);
void	prompt_loop(t_data *data);
int		msh_free(t_data *data);
int		msh_init(t_data *data);

void	print_result(t_cmd *token);
void	split_spaces(t_cmd *token, char *content);
void	del_token(void *content);
int		parsing(t_data *data);

void	str_arr_free(char **str);
int	ft_malloc(void **p, int length);

char	**unquote_split(char *s, char c);
int		count_tab_str(char **args);

int	termios_setup(t_data *data);

int     set_env(t_data *data);
int		update_env(t_data *data, char **entry, int len_entry);

char	**str_arr_add(char **sarr, char **entry, int len_entry);
void	ft_env(t_data *data, t_cmd *cmd);
#endif