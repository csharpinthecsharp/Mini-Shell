/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:37:12 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/02 16:35:19 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========================== */
/*        PROJECT MACROS      */
/* ========================== */
# define BUFFER_SIZE 42
# define CAT_SIZE    3

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
    char *path;             // Current working path
    int c_quote;            // Single quote count
    int c_big_quote;        // Double quote count
    int c_pipe;             // Pipe count
    int c_env_var;          // Env var count
}   t_data;

/* ========================== */
/*        FUNCTION PROTOS     */
/* ========================== */
// Path & Env
char    *getpath(char *buffer);

// Builtins
int     run_build_cmd(t_data *d, char *envp[]);
int     handle_pwd(char *argv, int count, char *path);
int     handle_exit(char *argv, int count);
int     handle_echo(char **argv, int count);

// Utils
int     ft_countword(char **spli_args);
int     filter_input(t_data *d, char *envp[]);
int     check_command(char **argv);
void    print_error(char *str_sub, char *str_cont);
int     run_custom_cmd(t_data *d);
int     zzz(t_data *d);
int     update_data(t_data *d);

#endif /* MINISHELL_H */
