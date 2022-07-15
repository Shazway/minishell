/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:57:35 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/15 17:03:05 by mdkhissi         ###   ########.fr       */
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
# include <fcntl.h>

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
	char	*fullpath;
	int		*fin;
	int		n_fin;
	int		n_fout;
	int		*fout;
}	t_cmd;

typedef struct s_pipex
{
	int fd[2];
}				t_pipex;

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
	int					n_cmd;
	t_pipex				*pips;
}	t_data;

int		cd(int ac, char **str);
int		is_double_dash(char *str);
int		change_path(char *str, char *path);
int		directory_exists(char *s);
char	*previous_dir(char *str);

int	ft_echo(int ac, char **av);
int		check_echo_n(char *str);

void	ft_env(t_data *data, t_cmd *cmd);
int		set_env(t_data *data);
int		update_env(t_data *data, char **entry, int len_entry);

int		shell_exit(int ac, char **av);

void	ft_export(t_data *data, t_cmd *cmd);
int		is_validid(char	*identifier, int len);

char	*pwd(void);

int		msh_init(t_data *data);
int		msh_free(t_data *data);
void	prompt_loop(t_data *data);

int		parsing(t_data *data);
void	print_result(t_cmd *token);
void	split_spaces(t_cmd *token, char *content);
void	del_token(void *content);

char	*concat_redir(char *str, char *redir, int *i, int is_double);
char	*check_redir(char *str, int *i);
char	*separate_redir(char *str);

int		signal_intercept(void);
void	sig_info(int signal, siginfo_t *s, void *trash);
int		termios_setup(t_data *data);

void	check_quote(char *type, char c);
int		count_words(char *s, char c);
int		malloc_words(char *s, char c, char **str, int count);
char	**fill(char *s, char c, char **str);
char	**unquote_split(char *s, char c);

void	str_arr_free(char **str);
int		str_arr_size(char **args);
char	**str_arr_add(char **sarr, char **entry, int len_entry);
int		ft_malloc(void **p, int length);
int		change_path(char *str, char *path);

void	free_pips(t_pipex *pips, int n);
void	free_cmd(void *vcmd);
void	search_cmds(t_data *data);
int		is_builtin(char *c_name);
void    execute(t_data *data);
void	run_cmd(t_data *data, t_cmd *cmd, int c_idx, int n_cmd);
char	*get_path(char *c_name, char **envr);
char	*getpath_worker(char *c_name, char **envr);
char	*parse_path(char **path_array, char *c_name);
void	print_fullpath(t_data *data);

#endif