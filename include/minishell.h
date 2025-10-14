/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:37:12 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/14 17:12:08 by ltrillar         ###   ########.fr       */
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
# define BUILT_IN        0
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
    char    **output_file;
    int     *cmd_state;
    int     *redirection_state;
    int     *cmd_quoted;
    size_t  cmd_count;
    char    *path;
    char    **envp;
    int     SHLVL;
    int     N_redir;
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
int     select_type(t_data *d);
int     run_custom_cmd(char **argv, t_data *d);
void    run_pipe_cmd(t_data *d, int N_pipe);
int     is_redirect(char **argv, t_data *d);
void handler_ctrl_c(int sig);

// Parsing & Input
int start_point_parsing(t_data *d);
char    **split(t_data *d);
char    ***split_commands(char **argv);
char    **get_args(char *s, t_data *d);
char    *get_one_arg(const char *s, int *i, int *is_dquote);
int     get_arg_length(const char *s, int *i, int *is_dquote);
int     ft_isspace(char arg);
int     ft_countword(char **spli_args);

// Environment & Path
char    *getpath(char *buffer, t_data *d);
char    *get_promptpath(char *buffer, t_data *d);
char    *replace_envvar(char *s, t_data *d, int *is_dquote);
void     update_data(t_data *d);
void     init_data(t_data *d);

int     is_valid_bin(char *str);

// Redirection & Pipes
void    alloc_redir_state(t_data *d);
void    alloc_cmd_state(t_data *d);
void    alloc_error_pipe(int N_pipe, int **var_pipe);
void    close_pipe(int **var_pipe, int N_pipe, int state);
char    **fix_redir_arg(t_data *d, char **argv, int redir_type, int index);
void alloc_buffer(char **buffer);

// Signals & Terminal
void    prepare_signals(void);
void    handler_ctrl_bs(int sig);

// Memory & Cleanup
void free_all(t_data *d, char *buffer);
void free_beforenewline(t_data *d, char *buffer);

// Misc
int     check_command(char **argv);
void    print_error(const char *str, const char *arg);
size_t  count_cmds(char ***cmds);
void redirect_left_left(t_data *d, int *pos, int fd_in);
void redirect_left(t_data *d, int *pos, int fd_in);
void redirect_right_right(t_data *d, int *pos, int fd_out);
void redirect_right(t_data *d, int *pos, int fd_out);
int is_numeric(const char *str);
int global_check(t_data *d);
char **duplicate_envp(char **envp);
char *up_shlvl(char *envp_i);
int isfulls(char *s);
void select_readline_mode(t_data *d);
int start_minishell(t_data *d);
void prepare_heredoc(t_data *d, int *pos);
void heredoc(t_data *d, int *pos);

#endif /* MINISHELL_H */