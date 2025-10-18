/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:37:12 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/18 02:38:22 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========================== */
/*         MACROS             */
/* ========================== */

// Buffer & Quote
# define BUFFER_SIZE     42
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
# define ERROR           8
# define REDIRECTION     9

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

/* ========================== */
/*       DATA STRUCTURES      */
/* ========================== */

typedef struct s_data
{
    int in_heredoc;
    int kill_heredoc;
    int kill_execution;
    int stdin_back;
    char    *input;
    char    **input_splitted;
    char    ***commands;
    int     *cmd_state;
    
    char    ***output_file;
    int     **redirection_state;
    int     *N_redir;
    int     N_redirfull;

    int     *cmd_quoted;
    int  cmd_count;
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

// Command & Execution
int     start_execution(t_data *d);
int     run_custom_cmd(char **argv, t_data *d);
void    run_non_stateful(t_data *d, int N_pipe);
int     is_redirect(char **argv, t_data *d, int *pos, int i);
void handler_ctrl_c(int sig);
void apply_output_redirections(t_data *d, int cmd_index);

// Parsing & Input
int start_point_parsing(t_data *d);
char    **split(t_data *d);
char    ***split_commands(char **argv);
char    **get_args(char *s, t_data *d);
char    *get_one_arg(char *s, int *i, int *is_dquote);
int     get_arg_length(const char *s, int *i, int *is_dquote);
int     ft_isspace(char arg);
int     ft_countword(char **spli_args);
int loop_into_arg(int i, char *s, int k, char *arg, int *j);
int count_args(char **argv, int start);
int check_pipe_syntax(char *input);
int check_in_check_pipe(char *input, int *pos);
int check_redirection_syntax(char *input);
int do_wehave_perm(char *str, t_data *d);
int check_output_ofeach(t_data *d, int index);
char *get_directory(const char *path);

// Environment & Path
char    *getpath(char *buffer, t_data *d);
char    *get_promptpath(char *buffer, t_data *d);
char    *replace_envvar(char *s, t_data *d, int *is_dquote);
void     update_data(t_data *d);
void     init_data(t_data *d);

int do_cmd_exist(char *str, t_data *d);
int do_file_exist(char *str, t_data *d);

// Redirection & Pipes
void    alloc_redir_state(t_data *d);
void    alloc_cmd_state(t_data *d);
void    alloc_error_pipe(int N_pipe, int **var_pipe);
void    close_pipe(int **var_pipe, int N_pipe, int state);
char **fix_redir_arg(t_data *d, char **argv, int index);
void alloc_buffer(char **buffer);
int put_cmdstate(int type, int *pos, int *is_stateful, t_data *d);

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

// Misc
int     check_command(char **argv);
void    print_error(const char *str, const char *arg);
int count_cmds(char ***cmds);
void redirect_left(t_data *d, int *pos, int fd_in, int i);
void redirect_right_right(t_data *d, int *pos, int fd_out, int i);
void redirect_right(t_data *d, int *pos, int fd_out, int i);
int is_numeric(const char *str, int state);
int global_check(t_data *d);
char **duplicate_envp(char **envp);
char *up_shlvl(char *envp_i);
int isfulls(char *s);
void select_readline_mode(t_data *d);
void start_minishell(t_data *d);
void prepare_heredoc(t_data *d, int *pos);
void heredoc(t_data *d, int *pos, int i);
void exit_ctrl_d(t_data *d, char *buf);
int is_empty(int i, t_data *d);

#endif /* MINISHELL_H */