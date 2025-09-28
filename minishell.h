/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:37:12 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/28 15:46:18 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define BUFFER_SIZE 42

#define BOLD_BLACK "\e[1;90m"
#define BOLD_GREEN "\e[47m"
#define BOLD_YELLOW "\e[1;93m"
#define BOLD_ROSE "\033[1;35m"
#define RESET "\e[0m"
#define RESET_TERMINAL "\033[2J\033[H"

#define GUN \
"\n" \
"                       ⣴⠋⢁⡉⠉⠉⠀⣀⣀⡀⠀⢀⣐⣒⣒⣒⡂⠠⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"                       ⡇⡀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠃⢠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"                       ⠁⠇⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"                       ⢸⢠⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"                       ⠀⡜⠀⢠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"                       ⠀⠇⡇⠸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"                       ⠀⢰⢠⠀⡆⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠤⠐⢊⣁⣧⡄⣀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"                       ⠀⠘⡈⡄⠡⡀⠀⠤⠄⠒⢂⣈⠡⣤⣲⣾⣿⣿⢿⢿⣛⠵⣯⢥⣒⠢⠄⣀⠀⠀\n" \
"                       ⠀⠀⢃⢡⣀⠠⠄⢒⣂⡭⣰⢦⣟⡮⢽⣚⡯⣜⠸⢛⣯⡵⠞⠋⠁⠀⠀⠀⢈⠵\n" \
"                       ⠀⠀⠈⣝⠣⡀⠪⣹⢢⠟⢫⠩⡖⡏⠽⢒⣩⣴⢾⠿⠛⠉⠢⡀⠀⢀⠤⠊⡡⠐\n" \
"                       ⠀⠀⠀⠈⠢⡈⠢⡈⠲⡩⢝⣊⣧⡾⠜⠊⡗⠋⠀⠀⣀⠄⡊⠔⢊⠠⠒⠁⠀⠀\n" \
"                       ⠀⠀⠀⠀⠀⠈⠢⡈⠢⡈⠉⠉⠁⠀⠀⠀⠈⠂⢐⡨⠐⣉⠄⠊⠀⠀⠀⠀⠀⠀\n" \
"                       ⠀⠀⠀⠀⠀⠀⠀⠈⠂⢌⠒⢄⠀⠀⢀⡠⠔⢊⡡⠔⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"                       ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠠⣉⣈⡡⠔⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"\n" \
"                              [welcome user]\n\n" 
#define CAT \
"⠀⠀⠀⢠⣾⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"⠀⠀⣰⣿⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"⠀⢰⣿⣿⣿⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣄⣀⣀⣤⣤⣶⣾⣿⣿⣿⡷\n" \
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁\n" \
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀\n" \
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀\n" \
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀\n" \
"⣿⣿⣿⡇⠀⡾⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀\n" \
"⣿⣿⣿⣧⡀⠁⣀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀\n" \
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠉⢹⠉⠙⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀\n" \
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣀⠀⣀⣼⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀\n" \
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠀⠤⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"⣿⣿⣿⣿⠿⣿⣿⣿⣿⣿⣿⣿⠿⠋⢃⠈⠢⡁⠒⠄⡀⠈⠁⠀⠀⠀⠀⠀⠀⠀\n" \
"⣿⣿⠟⠁⠀⠀⠈⠉⠉⠁⠀⠀⠀⠀⠈⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" \
"⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
#define TEMPLATE_SETUP_SCREEN RESET_TERMINAL BOLD_YELLOW GUN RESET
#define TEMPLATE_PROMPT " " BOLD_BLACK BOLD_GREEN " Minishell " RESET BOLD_YELLOW " $> " RESET
#define TEMPLATE_GOOD_BYE RESET_TERMINAL BOLD_YELLOW CAT BOLD_ROSE "[see you soon]\n" RESET


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
int check_command(char *input);
int try_input(char *input, char *envp[]);

#endif
