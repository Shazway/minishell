/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:57:35 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/28 01:25:39 by tmoragli         ###   ########.fr       */
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
# include <error.h>
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
	t_list				*cmd;
	int					n_cmd;
	int					ret;
	char				**env_str;
	char				*old_path;
	char				*relative_path;
	struct termios		termios;
	char				*prompt;
	char				*error_msh;
	t_pipex				*pips;
}	t_data;

typedef int				(*FP)(t_data *, int, char **);

typedef struct s_cmd
{
	int		i;
	char	*name;
	char	*lim;
	char	**args;
	char	*h_exp;
	int		ac;
	char	*fullpath;
	int		fin;
	int		fout;
	int		to_fork;
	int		builtin;
	FP		func;
}	t_cmd;

//-----------CD--------------//
int		cd(t_data *data, int ac, char **str);
int		is_double_dash(char *str);
int		is_dash(char	*str);
int		cd_home(char *path, char *name, t_data *data);
int		cd_dash(char *arg, t_data *data);
char	*concat_path(char *s1, char *s2);
int		change_path(char *goal, char *foldername, t_data *data);
char	*find_new_pwd(char *foldername, char **goal);
int		foldername_loop(char **foldername, char **new_path);
int		new_pwd(char *foldername, char **new_path);
char	*next_dir(char *foldername);
char	*previous_dir(char *path);
char	*next_dir(char *foldername);
void	update_pwd(t_data *data);
//------------------------------//

//-----------ECHO--------------//
int		ft_echo(t_data *data, int ac, char **av);
int		check_echo_n(char *str);
//------------------------------//

//-----------ENV---------------//
int		ft_env(t_data *data, int ac, char **av);
void	update_env(t_data *data, char **ids, char **entry, int len_entry);
char	*find_var(char **envr, char *entry);
char	*ft_replace(char *dest, char *src);
//------------------------------//

//-----------EXIT--------------//
int		shell_exit(t_data *data, int ac, char **av);
//------------------------------//

//-----------EXPORT------------//
int		ft_export(t_data *data, int ac, char **av);
int		export_worker(char **ids, char **entry, int ac, char **av);
int		is_validid(char	*identifier, int len);
void	free_pipes(t_data *data);
void	close_pipes(t_pipex *pips, int n);
//------------------------------//

//-----------PWD---------------//
int		pwd(t_data *data, int ac, char **av);
//------------------------------//

//-----------UNSET-------------//
int		ft_unset(t_data *data, int ac, char **av);
//------------------------------//

//-----------CMD---------------//
t_cmd	*init_cmd(int i);
void	search_cmds(t_data *data);
void	free_cmd(void *vcmd);
void	close_cmd_files(t_cmd *cmd);
void	cmd_notfound(char *cmd_name);
int		is_builtin(t_data *data, t_cmd *cmd);
char	*get_path(char *c_name, char **envr);
char	*parse_path(char **path_array, char *c_name);
void	print_fullpath(t_data *data);
//------------------------------//

//-----------EXECUTE-----------//
void	execute(t_data *data);
void	wait_cmds(t_data *data);
void	run_cmd(t_data *data, t_cmd *cmd, int i, int n);
void	close_unused_pipes(t_pipex *pips, int r, int w, int n);
void	exec_builtin(t_data *data, t_cmd *cmd);
int		here_doc(char *lim, int expand, char **envr, t_data *data);
int		heredoc_writer(int fd, char *buf, int expand, char **envr);
char	*extract_var(char *pvar);
void	alloc_pipes(t_data *data);
void	init_pipe(t_data *data, int i);
//------------------------------//

//-----------EXPAND-------------//
char	*expand_variables(t_data *data, char *str);
char	*get_end(char *str, int index);
char	*get_start(char *str);
char	*get_var(char *str, t_data *data);
char	*get_name(char	*str);
char	*replace_variables(char	*str, t_data *data);
//------------------------------//

//-----------MINISHELL----------//
void	minishell_sh(t_data *data);
int		msh_init(t_data *data);
int		msh_free(t_data *data);
void	msh_exit(t_data *data);
int		set_env(t_data *data);
//------------------------------//

//-----------PARSING------------//
int		parsing(t_data *data);
void	print_result(t_cmd *token);
void	delete_quotes(t_data *data);
void	split_spaces(t_cmd *token, char *content);
int		is_opened_quotes(t_data *data);
void	check_quote(char *type, char c);
char	*del_quote(char *str);
int		trim_quote_size(char *str);
char	*trim_quotes_fill(char *dest, char *str, int size);
char	*trim_quotes(t_data *data, char *str);
char	**unquote_split(char *s, char c);
//------------------------------//

//-----------REDIRECTIONS-------//
int		open_redirections(t_data *data);
int		setup_rfiles(t_cmd	*arg, int i, char **envr, t_data *data);
char	**eliminate_redirections(char **args);
char	**destroy_redirections(char **dest, char **args);
int		str_arr_size_r(char	**str);
int		is_redirection(char	*str, int type);
char	*concat_redir(char *str, char *redir, int *i, int is_double);
char	*check_redir(char *str, int *i);
int		open_redirections(t_data *data);
char	*separate_redir(char *str);
//------------------------------//

//-----------SIGNAL-------------//
void	secondary_handler(int signal, siginfo_t *s, void *trash);
int		signal_intercept(void);
void	sig_info_main(int signal, siginfo_t *s, void *trash);
int		termios_setup(t_data *data);
void	heredoc_handler(int signal, siginfo_t *s, void *trash);
//------------------------------//

//-----------UTILS---------------//
char	**str_arr_free(char **str);
void	str_arr_display(char **str);
int		str_arr_size(char **args);
char	**str_arr_del(char **sarr, char **entry, int len_entry);
char	**str_arr_add(char **sarr, char **entry, int len_entry);
char	*ft_str_zero(char	*str);
int		ft_malloc(void **p, int length);
int		*sarrdel_worker(char **sarr, char **entry, int len_entry, int *len_new);
void	*ft_free(void	*ptr);
//-------------------------------//

#endif