/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:37:12 by ltrillar          #+#    #+#             */
/*   Updated: 2025/11/06 17:05:08 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========================== */
/*         MACROS             */
/* ========================== */

// Status
# define FAILED 1
# define SUCCESS 0
# define ERROR -1

// Command Type
# define BIN 0
# define CUSTOM 1
# define STATEFUL 2

// Redirection Type
# define NOT_FOUND 3
# define LEFT 4
# define RIGHT 5
# define LEFT_LEFT 6
# define RIGHT_RIGHT 7
# define MISSING_BIN 8
# define ALONE_RR 10
# define ALONE_LL 11
# define ALONE_R 12
# define ALONE_L 13
# define ALONE_REDIR 14

/* ========================== */
/*        DEPENDENCIES        */
/* ========================== */

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

/* ========================== */
/*       DATA STRUCTURES      */
/* ========================== */

typedef struct s_arguments
{
	int				state_redir;
	char			*file;
	int				heredoc_quoted;
}					t_arguments;

typedef struct s_error
{
	char			*message;
	char			*argument;
	int				exit_code;
	struct s_error	*next;
}					t_error;

typedef struct s_cmd
{
	char			**arg;
	int				nb_redir;
	int				state_cmd;
	int				nb_arg;
	t_arguments		*arguments;
}					t_cmd;

typedef struct s_data
{
	int				nb_cmd;
	t_cmd			*cmd;
	int				fd_in;
	int				fd_out;
	int				stdin_back;
	char			*input;
	int				error_state;
	int				curr_alone_r;
	char			*path;
	char			**envp;
	int				last_fork_pid;
	int				exit_status;
	char			*new_path;
	int				defer_errors;
	t_error			*errors;
	struct termios	original_term;
	int				term_saved;
}					t_data;

typedef struct s_heredoc_ctx
{
	int				fd[2];
	int				stdin_backup;
	char			*delimiter;
	int				should_expand;
	t_data			*d;
}					t_heredoc_ctx;

/* ========================== */
/*      FUNCTION PROTOTYPES   */
/* ========================== */

// Builtins
void				free_cmds(t_data *d);
int					pipe_init(int N_pipe, int **var_pipe);
int					handle_pwd(char *argv, int count, char *path);
int					handle_exit(t_data *d, char **argv, int count);
int					handle_echo(char **argv, int count);
int					handle_export(char **argv, int count, t_data *d);
int					handle_cd(char **argv, int count, t_data *d);
int					handle_unset(char **argv, int count, t_data *d);
int					handle_env(char **argv, int count, t_data *d);
int					count_redir(char **argv);
int					count_commands(char **argv);
int					pre_exec_prepare(t_data *d, int i);
int					pre_execution(t_data *d);
int					run_custom_cmd(char **argv, t_data *d);
int					handle_quote_state(char *input, int *pos, char *quote);
int					count_arg(char **argv, int i);
int					handle_error_malloc(char *s);
void				heredoc_ctrl_c(int sig);
void				exec_with_path(char **paths, t_cmd *cmd, t_data *d);
void				exec_built_inpipe(int **pipe, t_data *d, int n_pipe,
						int *pos);
void				exec_custom_inpipe(int **pipe, t_data *d, int n_pipe,
						int *pos);
void				exec_alone_redir_inpipe(int **pipe, t_data *d, int n_pipe,
						int *pos);
void				handle_pipe(int **pipe, int *pos, int n_pipe);
void				handle_redirections(t_data *d, int *pos, int *fd_out,
						int *fd_in);
void				handle_heredocs(t_data *d, int *pos);
void				execute_command_by_type(int **pipe, t_data *d, int n_pipe,
						int *pos);
void				handle_bin(t_cmd *cmd, t_data *d);
void				restore_stdin(t_data *d);
void				wait_for_children(t_data *d, pid_t last_pid);
void				handle_child_status(t_data *d, pid_t wpid, int status,
						pid_t last_pid);
void				start_execution(t_data *d);
void				handler_ctrl_c(int sig);
void				free_split(char **argv);
bool				put_redir(t_data *d, int cmd_index, int arg_index,
						int redir_index);

// Parsing & Input
char				*get_directory(const char *path);
int					split(t_data *d);
char				**get_args(char *s, t_data *d, int *is_dquote, char **argv);
char				*get_one_arg(char *s, int *i, int *is_dquote);
int					split_commands(char **argv, t_data *d);
int					start_point_parsing(t_data *d);
int					get_arg_length(const char *s, int *i, int *is_dquote);
int					ft_isspace(char arg);
int					ft_countword(char **spli_args);
int					is_valid_identifier(const char *str);
int					pipe_syntax(char *input);
int					redirection_syntax(char *input);
int					check_output_ofeach(t_cmd *cmd, t_data *d);
int					get_expanded_size(char *s, t_data *d, int is_dquote);
char				*get_env_string(t_data *d, char *s);
int					break_free(char *arg, char *raw_arg);

// Environment & Path
char				*get_path(t_data *d);
char				*get_promptpath(t_data *d);
char				*replace_envvar(char *s, t_data *d, int *is_dquote, char *arg);
int	                handle_expansion(char *s, t_data *d, char **arg, int *indices);
void				init_data(t_data *d);
int					is_available(char *str, t_data *d);
void				execve_error(char *cmd);
bool				check_alone_redir(char **argv);

// Redirection & Pipes
void				close_pipe(int **var_pipe, int N_pipe, int state);
void				set_error(t_data *d, int exit_code, char *error_s,
						char *tmp);
char				**fix_redir_arg(t_cmd *cmd);
int					put_cmdstate(int type, int *is_stateful, t_cmd *cmd,
						t_data *d);
int					stat_error_h(t_data *d, char *tmp);
int					error_h(t_data *d, char *tmp);
bool				is_alone_redir(char **argv, t_data *d);

// Signals & Terminal
void				prepare_signals(void);
void				handler_ctrl_bs(int sig);

// Memory & Cleanup
void				free_all(t_data *d);
void				free_beforenewline(t_data *d);
char				*ft_get_env(t_data *d, char *requested);
int					check_non_bin(t_cmd *cmd, int type, int *is_stateful,
						t_data *d);
int					check_in_check_redir(char *input, int *pos, char *quote);
int					check_in_check_pipe(char *input, char *quote, int *pos);

// Misc
int					check_command(char **argv, t_data *d);
void				print_error(const char *str, const char *arg);
int					error_export(char *equal_sign, char **arg_ptr);
void				check_status_error(t_data *d, char *file, char *error_s);
int					check_dir_right(t_cmd *c, t_data *d, char *dir, int i);
int					check_dir_left(t_cmd *cmd, t_data *d, char *file, int i);
int					count_cmds(char ***cmds);
void				redirect_left(t_data *d, int *pos, int fd_in, int i);
void				redirect_right_right(t_data *d, int *pos, int fd_out,
						int i);
void				redirect_right(t_data *d, int *pos, int fd_out, int i);
int					is_numeric(const char *str, int state);
int					syntax_validation(t_data *d);
char				**duplicate_envp(char **envp);
char				*up_shlvl(char *envp_i);
int					isfulls(char *s);
int					is_key_exitstatus(char *s, int quote_off);
void				select_readline_mode(t_data *d);
void				start_minishell(t_data *d);
void				prepare_heredoc(t_data *d, int *pos);
void				heredoc(t_data *d, int *pos, int i, int is_last);
int					heredoc_read_loop(int fd_write, char *delimiter, t_data *d,
						int should_expand);
int					heredoc_parent_should_abort(t_heredoc_ctx *ctx, int status,
						int interrupted);
void				heredoc_cleanup_on_failure(t_heredoc_ctx *ctx,
						int error_state, int reset_terminal);
void				restore_terminal_settings(t_data *d);
void				exit_ctrl_d(t_data *d);
int					is_empty(t_data *d, int cmd_index, int arg_index);
char				**remove_empty_var(char **tokens);
void				h_expand_size(char **s, int *len, t_data *d);
char				*expand_arg(char *raw_arg, t_data *d, int *is_dquote);
void				add_deferred_error(t_data *d, int exit_code,
						const char *message, const char *argument);
void				flush_deferred_errors(t_data *d);
void				clear_deferred_errors(t_data *d);
int					expand_exit_status(t_data *d, int *len);

#endif /* MINISHELL_H */
