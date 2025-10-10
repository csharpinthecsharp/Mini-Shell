/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:37:12 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/10 00:13:30 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========================== */
/*        PROJECT MACROS      */
/* ========================== */
# define BUFFER_SIZE 42
# define CAT_SIZE    3
#define QUOTE_TRUE 1
#define QUOTE_FALSE 0
#define PIPE '|'
#define QUOTE '\''
#define BIG_QUOTE '\"'
#define ENV_VAR '$'

// GLOBAL
#define FAILED 1
#define SUCCESS 0

// COMMAND TYPE PART CHECK
#define BUILT_IN 0
#define CUSTOM 1
#define STATEFUL 2

// REDIRECTION PART CHECK
#define NOT_FOUND 3
#define LEFT 4
#define RIGHT 5
#define LEFT_LEFT 6
#define RIGHT_RIGHT 7
#define ERROR 8
#define REDIRECTION 9

/* ========================== */
/*        DEPENDENCIES        */
/* ========================== */
# include "../libft/libft.h"
# include <stdio.h>      // printf
# include <stdlib.h>     // malloc, free, getenv
# include <unistd.h>     // write, read, fork, execve, pipe, dup, dup2, chdir
# include <fcntl.h>      // open, close
# include <sys/wait.h>   // wait, waitpid
# include <signal.h>     // signal, sigaction, kill
# include <sys/stat.h>   // stat, lstat, fstat, unlink
# include <dirent.h>     // opendir, readdir, closedir
# include <string.h>     // strerror
# include <errno.h>      // perror
# include <termios.h>    // tcsetattr, tcgetattr
# include <termcap.h>    // tgetent, tputs
# include <readline/readline.h>  // readline
# include <readline/history.h>   // add_history, rl_clear_history

/* ========================== */
/*        DATA STRUCTURES     */
/* ========================== */
typedef struct s_data
{
    char *input;            // Raw user input
    char **input_splitted;  // Tokenized input
    char ***commands;

    char **output_file;

    int *cmd_state;
    int *redirection_state;
    
    size_t cmd_count;
    
    char *path;             // Current working path
    char **envp;
    int exit_status;
}   t_data;

/* ========================== */
/*        FUNCTION PROTOS     */
/* ========================== */
// Path & Env
char    *getpath(char *buffer);

// Builtins
int     handle_pwd(char *argv, int count, char *path);
int     handle_exit(char **argv, int count);
int     handle_echo(char **argv, int count);
int     handle_export(char **argv, int count, t_data *d);
int     handle_cd(char **argv, int count, t_data *d);
int select_type(t_data *d);

// Utils
int     ft_countword(char **spli_args);
int     filter_input(t_data *d);
int     check_command(char **argv);
void print_error(const char *str, const char *arg);
int     run_custom_cmd(char **argv, t_data *d);
int     update_data(t_data *d);
void    run_pipe_cmd(t_data *d, int N_pipe);
char    ***split_commands(char **argv);
char    *get_promptpath(char *buffer);
int     ft_isspace(char arg);
int pipe_count(char **argv);
char    *replace_envvar(char *s, t_data *d);
char *get_one_arg(const char *s, int *i);
char    **get_args(char *s, t_data *d);
char    **split(t_data *d);
int get_arg_length(const char *s, int *i);
void free_all(t_data *d);
void close_pipe(int **var_pipe, int N_pipe, int state);
int is_valid_bin(char *str);
size_t count_cmds(char ***cmds);
void handler_ctrl_bs(int sig);
void prepare_signals(void);
void alloc_error_pipe(int N_pipe, int **var_pipe);
void alloc_cmd_state(t_data *d);
void exec_redirect_left(char **argv);
int is_redirect(char **argv);
void alloc_redir_state(t_data *d);
char **fix_redir_arg(t_data *d, char **argv, int redir_type, int index);

#endif /* MINISHELL_H */
