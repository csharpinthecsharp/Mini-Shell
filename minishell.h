/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:37:12 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/02 12:43:00 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define BUFFER_SIZE 42

#define BOLD_BLACK      "\001\e[1;30m\002"
#define BOLD_RED        "\001\e[1;91m\002"
#define BACKGROUND_YELLOW "\001\e[0;103m\002"
#define BOLD_YELLOW     "\001\e[1;93m\002"
#define BOLD_ROSE       "\001\033[1;35m\002"
#define BOLD_GREEN      "\001\e[1;92m\002"
#define RESET           "\001\e[0m\002"
#define RESET_TERMINAL  "\033[2J\033[H"


#define GUN \
"                   _\n\
                   |\\___/|                      \\\\\n\
                   )     (    |\\_/|              ||\n\
                  =\\     /=   )a a `,_.-\"\"\"\"\"-.  //\n\
                    )===(    =\\Y_= /          \\//\n\
                   /     \\     `\"`\\       /    /\n\
                   |     |         |    \\ |   /\n\
                  /       \\         \\   /- \\  \\\n\
                  \\       /         || |  // /`\n\
           _/\\_/\\_/\\_   _/_/\\_/\\_/\\_((_|\((_//\\_/\\_/\\_/\\_ \n" \
"\n                         "BACKGROUND_YELLOW BOLD_BLACK" <[minishell_42]> \n\n" 

#define ERROR_PREFIX \
BOLD_RED \
" .∧,,,∧\n" \
"(  ̳• · • ̳)\n" \
"/    づ▄︻デ══━一 > "

#define DOOR \
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⢀⣀⡠⠤⠴⠚⣿⠃\n" \
"⠀⠸⣿⡭⣭⣿⣽⣿⣿⣿⣿⣿⣿⣿⣽⣿⡿⠓⠚⠉⣉⣀⣤⡤⣴⠀⣿⠀\n" \
"⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢰⠞⢩⠀⢻⡏⠀⡏⠀⣿⠄\n" \
"⠀⢠⣟⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢸⠀⢸⠀⢸⡇⠀⠃⠀⣿⠂\n" \
"⠀⢘⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢸⠀⢸⠀⢸⡇⠀⡇⠀⣿⡇\n" \
"⠀⠈⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢸⠀⢸⠀⢸⡇⠀⣷⠀⣿⡇\n" \
"⠀⣠⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢸⠀⢸⠀⢸⡇⠀⣿⣼⣿⡇\n" \
"⠀⡃⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠘⠛⠛⠒⠛⠓⠛⠛⣿⣿⡇\n" \
"⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢰⠦⢠⠀⢤⣤⣤⣄⠋⣿⡇\n" \
"⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢸⠀⢸⠀⢸⡇⠈⣿⠀⣿⡇\n" \
"⠀⢸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢸⠀⢸⠀⢸⡇⠀⣿⠀⣿⡇\n" \
"⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢸⣄⢸⠠⣼⡇⠀⣿⠀⣿⡇\n" \
"⠀⣸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠉⠉⠀⠛⠚⠯⠿⠀⣿⡇\n" \
"⠠⢿⣿⣷⣶⣶⣶⠶⢶⡶⢶⣶⣶⣶⣶⢿⣶⣤⣄⣀⣀⠀⠀⠀⢨⠀⣿⡇\n" \
"⠀⠀⠀⠈⠀⠐⠒⠒⠀⠀⠀⠘⠁⠈⠀⠀⠀⠀⠉⠉⢛⠉⠑⠒⠠⠤⢿⠇\n"
#define TEMPLATE_SETUP_SCREEN RESET_TERMINAL BOLD_YELLOW GUN RESET
#define TEMPLATE_PROMPT " " BACKGROUND_YELLOW BOLD_BLACK " Minishell " RESET BOLD_YELLOW " $> " RESET
#define TEMPLATE_GOOD_BYE RESET_TERMINAL BOLD_YELLOW DOOR "[see you soon]\n" RESET

#define CAT_SIZE 3

typedef struct s_data
{
    char *input;
    char **input_splitted;
    char **input_quote;
    char *path;
    int quotted_words;
} t_data;

#include "libft/libft.h"
#include <stdio.h>  
/* STDIO.H RELATED >
* -> printf | Print formatted output to stdout.
*/

#include <stdlib.h>  
/* STDLIB.H RELATED >
* -> malloc | Allocate memory dynamically.
* -> free | Free previously allocated memory.
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
/* UNISTD.H RELATED >
* -> write | Write to a file descriptor.
* -> read | Read from a file descriptor.
* -> access | Check user's permissions for a file.
* -> open | Open a file.
* -> close | Close a file descriptor.
* -> fork | Create a new process.
* -> wait | Wait for child process to change state.
* -> waitpid | Wait for specific child process.
* -> wait3 | Wait for child process with resource usage.
* -> wait4 | Wait for child with extended info.
* -> exit | Terminate the calling process.
* -> getcwd | Return absolute path of current directory.
* -> chdir | Change current working directory.
* -> execve | Execute a program.
* -> dup | Duplicate a file descriptor.
* -> dup2 | Duplicate to a specific file descriptor.
* -> pipe | Create a unidirectional data channel.
*/

#include <signal.h>  
/* SIGNAL.H RELATED >
* -> signal | Set signal handler.
* -> sigaction | Examine and change signal action.
* -> sigemptyset | Initialize signal set to exclude all.
* -> sigaddset | Add signal to signal set.
* -> kill | Send signal to a process.
*/

#include <sys/stat.h>  
/* SYS/STAT.H RELATED >
* -> stat | Get file status.
* -> lstat | Get file status, not following symlinks.
* -> fstat | Get file status from file descriptor.
* -> unlink | Remove a file.
*/

#include <dirent.h>  
/* DIRENT.H RELATED >
* -> opendir | Open a directory stream.
* -> readdir | Read a directory entry.
* -> closedir | Close a directory stream.
*/

#include <string.h>  
/* STRING.H RELATED >
* -> strerror | Return error message string.
*/

#include <errno.h>  
/* ERRNO.H RELATED >
* -> perror | Print error message to stderr.
*/

#include <termios.h>  
/* TERMIOS.H RELATED >
* -> isatty | Check if fd refers to terminal.
* -> ttyname | Get terminal name.
* -> ttyslot | Get slot number of terminal.
* -> ioctl | Control device parameters.
* -> tcsetattr | Set terminal attributes.
* -> tcgetattr | Get terminal attributes.
*/

#include <termcap.h>  
/* TERMCAP.H RELATED >
* -> tgetent | Load terminal entry.
* -> tgetflag | Get boolean terminal capability.
* -> tgetnum | Get numeric terminal capability.
* -> tgetstr | Get string terminal capability.
* -> tgoto | Construct cursor movement string.
* -> tputs | Output terminal string.
*/

#include <stdlib.h>  
/* ENVIRONMENT RELATED >
* -> getenv | Get environment variable.
*/
#include <readline/readline.h>
#include <readline/history.h>
/* READLINE RELATED >
* -> readline | Read line from terminal.
* -> rl_clear_history | Clear history list.
* -> rl_on_new_line | Signal new line.
* -> rl_replace_line | Replace current line buffer.
* -> rl_redisplay | Refresh terminal display.
* -> add_history | Add line to history.
*/

char *getpath(char *buffer);
int run_build_cmd(t_data *d, char *envp[]);
int ft_countword(char **spli_args);
int filter_input(t_data *d, char *envp[]);
int check_command(char **argv);
void print_error(char *str_sub, char *str_cont);
int run_custom_cmd(t_data *d);
int handle_pwd(char *argv, int count, char *path);
int handle_exit(char *argv, int count);
int handle_echo(char **argv, int count);
int filter_quote(t_data *d);
int zzz(char *input);

#endif
