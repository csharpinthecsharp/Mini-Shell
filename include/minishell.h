/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:37:12 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/06 01:28:25 by ltrillar         ###   ########.fr       */
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

#define FAILED 1
#define SUCCESS 0

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
    char *path;             // Current working path
    char **envp;
    unsigned int exit_status;
}   t_data;

/* ========================== */
/*        FUNCTION PROTOS     */
/* ========================== */
// Path & Env
char    *getpath(char *buffer);

// Builtins
int     run_build_cmd(t_data *d, char *envp[]);
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
int     run_custom_cmd(t_data *d);
int     update_data(t_data *d);
void    pipe_the_pipe(char ***commands, char **envp, int N_pipe);
char    ***split_commands(char **argv);
char    *get_promptpath(char *buffer);
int     ft_isspace(char arg);
int pipe_count(char **argv);
char    *replace_envvar(char *s, t_data *d);
char *get_one_arg(const char *s, int *i);
char    **get_args(char *s, t_data *d);
char    **split(t_data *d);
int get_arg_length(const char *s, int *i);
#endif /* MINISHELL_H */
