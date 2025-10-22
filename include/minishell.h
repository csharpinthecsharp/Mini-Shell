/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:37:12 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 16:13:28 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========================== */
/*         MACROS             */
/* ========================== */

// Buffer & Quote
# define BUFFER_SIZE     1000
# define CAT_SIZE        3
# define QUOTE_TRUE      1
# define QUOTE_FALSE     0
# define PIPE            '|'
# define QUOTE           '\''
# define BIG_QUOTE       '\"'
# define ENV_VAR         '$'

// Status
# define FAILED          1
# define SUCCESS         0
# define ERROR           -1

// Command Type
# define BIN             0
# define CUSTOM          1
# define STATEFUL        2

// Redirection Type
# define NOT_FOUND       3
# define LEFT            4
# define RIGHT           5
# define LEFT_LEFT       6
# define RIGHT_RIGHT     7
# define REDIRECTION     9
# define ALONE_RR       10
# define ALONE_LL       11
# define ALONE_R        12
# define ALONE_L        13
# define ALONE_REDIR    14

/* ========================== */
/*        DEPENDENCIES        */
/* ========================== */

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

/* ========================== */
/*       DATA STRUCTURES      */
/* ========================== */

typedef struct s_arguments
{
    int state_redir;
    char *file;
} t_arguments;

typedef struct s_cmd
{
    char **arg;
    int nb_redir;
    int state_cmd;
    int nb_arg;

    t_arguments *arguments;
} t_cmd;

typedef struct s_data
{
    int nb_cmd;
    t_cmd *cmd;

    int fd_in;
    int fd_out;
    int stdin_back;
    char    *input;
    char    **input_splitted;
    int     error_state;
    int     curr_alone_r;
    char    *path;
    char    **envp;
    int     SHLVL;
    int     last_fork_pid;
    int     exit_status;
    char    *new_path;
}   t_data;

/* ========================== */
/*      FUNCTION PROTOTYPES   */
/* ========================== */

// Builtins
int     handle_pwd(char *argv, int count, char *path);
int     handle_exit(char **argv, int count);
int     handle_echo(char **argv, int count);
int     handle_export(char **argv, int count, t_data *d);
int     handle_cd(char **argv, int count, t_data *d);
int     handle_unset(char **argv, int count, t_data *d);
int     handle_env(char **argv, int count, t_data *d);
void heredoc_ctrl_c(int sig);
int count_redir(char **argv);
void exec_built_inpipe(int **pipe, t_data *d, int n_pipe, int *pos);
void exec_custom_inpipe(int **pipe, t_data *d, int n_pipe, int *pos);
void exec_alone_redir_inpipe(int **pipe, t_data *d, int n_pipe, int *pos);
void handle_pipe(int **pipe, int *pos, int n_pipe);
void handle_redirections(t_data *d, int *pos, int *fd_out, int *fd_in);
void handle_heredocs(t_data *d, int *pos);
void execute_command_by_type(int **pipe, t_data *d, int n_pipe, int *pos);
void handle_bin(t_cmd *cmd, t_data *d);
int count_commands(char **argv);
void restore_stdin(t_data *d);
void wait_for_children(t_data *d, pid_t last_pid);
void handle_child_status(t_data *d, pid_t wpid, int status, pid_t last_pid);
int     pre_execution(t_data *d);
void     start_execution(t_data *d);
bool put_redir(t_data *d, int cmd_index, int arg_index, int redir_index);
void handler_ctrl_c(int sig);
int run_custom_cmd(char **argv, t_data *d);
int	handle_quote_state(char *input, int *pos, char *quote);
int count_arg(char **argv, int i);
void free_split(char **argv);
int handle_error_malloc(char *s);

// Parsing & Input
int start_point_parsing(t_data *d);
char    **split(t_data *d);
int     split_commands(char **argv, t_data *d);
char    **get_args(char *s, t_data *d);
char    *get_one_arg(char *s, int *i, int *is_dquote);
int     get_arg_length(const char *s, int *i, int *is_dquote);
int     ft_isspace(char arg);
int     ft_countword(char **spli_args);
int loop_into_arg(int i, char *s, int k, char *arg, int *j);
int pipe_syntax(char *input);
int redirection_syntax(char *input);
int check_output_ofeach(t_cmd *cmd, t_data *d);
char *get_directory(const char *path);

// Environment & Path
char    *getpath(char *buffer, t_data *d);
char    *get_promptpath(t_data *d);
char    *replace_envvar(char *s, t_data *d, int *is_dquote);
void     update_data(t_data *d);
void     init_data(t_data *d);

int is_available(char *str, t_data *d);
void execve_error(char *cmd);
bool check_alone_redir(char **argv);

// Redirection & Pipes
void    alloc_redir_state(t_data *d);
void    alloc_cmd_state(t_data *d);
void    alloc_error_pipe(int N_pipe, int **var_pipe);
void    close_pipe(int **var_pipe, int N_pipe, int state);
char **fix_redir_arg(t_cmd *cmd);
void alloc_buffer(char **buffer);
int put_cmdstate(int type, int *is_stateful, t_cmd *cmd, t_data *d);
bool is_alone_redir(char **argv, t_data *d);

// Signals & Terminal
void    prepare_signals(void);
void    handler_ctrl_bs(int sig);

// Memory & Cleanup
void free_all(t_data *d, char *buffer);
void free_beforenewline(t_data *d, char *buffer);
void alloc_output_file(t_data *d);
void alloc_start_execution(t_data *d);
void alloc_parse_args(char ***argv, int len);
char *ft_get_env(t_data *d, char *requested);
int check_non_bin(t_cmd *cmd, int type, int *is_stateful, t_data *d);
int	check_in_check_redir(char *input, int *pos, char *quote);
int	check_in_check_pipe(char *input, char *quote, int *pos);

// Misc
int     check_command(char **argv, t_data *d);
void    print_error(const char *str, const char *arg);
int count_cmds(char ***cmds);
void redirect_left(t_data *d, int *pos, int fd_in, int i);
void redirect_right_right(t_data *d, int *pos, int fd_out, int i);
void redirect_right(t_data *d, int *pos, int fd_out, int i);
int is_numeric(const char *str, int state);
int syntax_validation(t_data *d);
char **duplicate_envp(char **envp);
char *up_shlvl(char *envp_i);
int isfulls(char *s);
void select_readline_mode(t_data *d);
void start_minishell(t_data *d);
void prepare_heredoc(t_data *d, int *pos);
void heredoc(t_data *d, int *pos, int i);
void exit_ctrl_d(t_data *d, char *buf);
int is_empty(t_data *d, int cmd_index, int arg_index);

#endif /* MINISHELL_H */