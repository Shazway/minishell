/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:57:35 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/23 00:25:14 by tmoragli         ###   ########.fr       */
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

# define R_DIR 1
# define R_DDIR 2
# define L_DIR 3
# define L_DDIR 4

extern struct sigaction	g_signals;

typedef struct s_pipex
{
	int	fd[2];
}				t_pipex;

typedef struct s_data
{
	char				*input;
	char				**env_str;
	char				*relative_path;
	char				*old_path;
	struct termios		termios;
	int					n_cmd;
	int					ret;
	t_pipex				*pips;
	t_list				*cmd;
	char				*prompt;
}	t_data;

typedef int (*FP)(t_data *, int, char **);

typedef struct s_cmd
{
	int		i;
	char	*name;
	char	**args;
	int		ac;
	char	*fullpath;
	int		fin;
	int		fout;
	int		no_fork;
	int		builtin;
	FP		func;
}	t_cmd;

//--------------CD---------------//
int		cd(t_data *data, int ac, char **str);
int		is_double_dash(char *str);
int		is_dash(char	*str);
int		cd_home(char *path, char *name, t_data *data);
int		cd_dash(char *arg, t_data *data);
char	*concat_path(char *s1, char *s2);
int		change_path(char *goal, char *foldername, t_data *data);

int		ft_echo(t_data *data, int ac, char **av);
int		check_echo_n(char *str);

int		ft_env(t_data *data, int ac, char **av);
int		set_env(t_data *data);
int		update_env(t_data *data, char **entry, int len_entry);

int		shell_exit(t_data *data, int ac, char **av);

char	*expand_variables(t_data *data, char *str);
char	*get_end(char *str, int index);
char	*get_start(char *str);
char	*get_var(char *str, t_data *data);
char	*get_name(char	*str);
int		ft_export(t_data *data, int ac, char **av);
int		is_validid(char	*identifier, int len);

int		pwd(t_data *data, int ac, char **av);


int		open_redirections(t_data *data);
int		setup_rfiles(t_cmd	*arg, int i, char **envr, t_data *data);
char	**eliminate_redirections(char **args);
char	**destroy_redirections(char **dest, char **args);
int		str_arr_size_r(char	**str);
int		is_redirection(char	*str, int type);

int		msh_init(t_data *data);
int		msh_free(t_data *data);
void	prompt_loop(t_data *data);

int		parsing(t_data *data);
void	print_result(t_cmd *token);
void	split_spaces(t_cmd *token, char *content);
void	del_token(void *content);
t_cmd	*init_cmd(int i);

char	*concat_redir(char *str, char *redir, int *i, int is_double);
char	*check_redir(char *str, int *i);
int		open_redirections(t_data *data);
char	*separate_redir(char *str);

void	secondary_handler(int signal, siginfo_t *s, void *trash);
int		signal_intercept(void);
void	sig_info_main(int signal, siginfo_t *s, void *trash);
int		termios_setup(t_data *data);

void	check_quote(char *type, char c);
int		count_words(char *s, char c);
int		malloc_words(char *s, char c, char **str, int count);
char	**fill(char *s, char c, char **str);
char	**unquote_split(char *s, char c);

void	str_arr_free(char **str);
void	str_arr_display(char **str);
int		str_arr_size(char **args);
char	**str_arr_add(char **sarr, char **entry, int len_entry);
int		ft_malloc(void **p, int length);

void	free_pipes(t_data *data);
void	close_pipes(t_pipex *pips, int n);
void	close_cmd_files(t_cmd *cmd);

void	free_cmd(void *vcmd);
void	search_cmds(t_data *data);
int		is_builtin(t_cmd *cmd);
void	execute(t_data *data);
void	run_cmd(t_data *data, t_cmd *cmd, int i, int n);
char	*get_path(char *c_name, char **envr);
char	*parse_path(char **path_array, char *c_name);
void	print_fullpath(t_data *data);
void	cmd_notfound(char *cmd_name);

char	*ft_strsetchr(const char *s, char *set);
char	*find_var(char **envr, char *entry);
char	*replace_variables(char	*str, t_data *data);
char	*extract_var(char *pvar);
void	heredoc_writer(int fd, char *buf, int expand, char **envr);
int		here_doc(char *lim, int expand, char **envr);
char	*get_var(char *str, t_data *data);
void	exec_builtin(t_data *data, t_cmd *cmd);
int		nofork_builtin(char *fullpath);
int		ft_unset(t_data *data, int ac, char **av);

char	*get_pwd(t_data *data);
void	wait_cmds(t_data *data);
void	msh_exit(t_data *data);

void	alloc_pipes(t_data *data);
void	init_pipe(t_data *data, int i);

void	close_unused_pipes(t_pipex *pips, int r, int w, int n);

int		is_path(char *s);

#endif