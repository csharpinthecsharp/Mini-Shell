/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 20:21:34 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
 
/*
 * Sélectionne le type de chaque commande (custom, built-in, etc.)
 * Gère les redirections et lance l'exécution des pipes.
 */
int select_type(t_data *d)
{
    size_t i = 0;
    alloc_cmd_state(d);
    alloc_redir_state(d);
    d->output_file = malloc(sizeof(char *) * BUFFER_SIZE);

    i = 0;
    int is_stateful = 0;
    while (i <= d->cmd_count)
    {
        int type = check_command(d->commands[i]);
        int redir_type = is_redirect(d->commands[i], d);
        
        if (redir_type > NOT_FOUND)
        {
            (*d).redirection_state[i] = redir_type;
            d->commands[i] = fix_redir_arg(d, d->commands[i], redir_type, i);
            if (d->commands[i][0] == NULL)
            {
                d->exit_status = 2;
                print_error("syntax error near unexpected token `newline'", "!");
                return (0);
            }
        }
        else
            (*d).redirection_state[i] = 0;
            
        if (type == CUSTOM)
            (*d).cmd_state[i] = CUSTOM;
        else if (type == STATEFUL)
        {
            is_stateful = 1;
            if (d->cmd_count == 0)
                run_custom_cmd(d->commands[i], d);
            else
                d->exit_status = 1;
        }
        else if (type == BUILT_IN)
        {
            if (is_valid_bin(d->commands[i][0]) == SUCCESS)
                (*d).cmd_state[i] = BUILT_IN;
            else
            {
                print_error("command not found", d->commands[i][0]);
                d->exit_status = 127;
            } 
        }
        i++;
    }
    if (is_stateful == 0)
        run_pipe_cmd(d, d->cmd_count);
    return (SUCCESS);
}

/*
 * Retourne le dernier argument (utilisé pour les redirections de sortie).
 */
static char *send_output(char **argv, int redir_state)
{
    (void)redir_state;
    int i = 0;
    while (argv[i + 1])
        i++;
    return (strdup(argv[i]));
}

/*
 * Corrige les arguments pour les redirections (ne garde que les bons).
 * Retourne un tableau d'arguments sans la redirection.
 */
char **fix_redir_arg(t_data *d, char **argv, int redir_type, int index)
{
    int i = 0;
    while (argv[i])
    {
        if (ft_strncmp(argv[i], ">>", 2) == 0)
            break;
        else if (ft_strncmp(argv[i], "<<", 2) == 0) 
            break;
        else if (ft_strncmp(argv[i], ">", 1) == 0)
            break;
        else if (ft_strncmp(argv[i], "<", 1) == 0) 
            break;
        i++;
    }

    if (i < 1)
    {
        if (argv[0] && ft_strncmp(argv[0], "echo", 4) == 0)
            return argv;
        argv[0] = NULL;
        return (argv);
    }
    char **dup = malloc(sizeof(char *) * (i + 1));
    if (!dup)
    {
        perror("malloc failed");
        return (NULL);        
    }
    int j = 0;
    if (redir_type == RIGHT || redir_type == LEFT
        || redir_type == RIGHT_RIGHT 
        || redir_type == LEFT_LEFT)
    {
        while (j < i)
        {
            dup[j] = ft_strdup(argv[j]);
            j++;
        }
    }
    (*d).output_file[index] = send_output(argv, redir_type);
    dup[i] = NULL;
    return (dup);
}

static void exec_custom_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    int fd_out = 0;
    int fd_in = 0;
    if (d->cmd_state[*pos] == CUSTOM)
    {
        if (N_pipe > 0 || d->N_redir > 0)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                if (N_pipe > 0)
                {
                    if (*pos > 0)
                        dup2(var_pipe[*pos - 1][0], STDIN_FILENO);
                    if (*pos < N_pipe)
                        dup2(var_pipe[*pos][1], STDOUT_FILENO);

                    close_pipe(var_pipe, N_pipe, 1);
                }
                if (d->redirection_state[*pos] == RIGHT)
                    redirect_right(d, pos, fd_out);
                else if (d->redirection_state[*pos] == RIGHT_RIGHT)
                    redirect_right_right(d, pos, fd_out);
                else if (d->redirection_state[*pos] == LEFT)
                    redirect_left(d, pos, fd_in);
                run_custom_cmd(d->commands[*pos], d);
                exit(d->exit_status);
            }
            else if (pid > 0)
                d->last_fork_pid = pid;
        }
        else
            run_custom_cmd(d->commands[*pos], d);
    }
}

static void exec_built_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    int fd_out = 0;
    int fd_in = 0;
    pid_t pid = fork();
    if (pid == 0)
    {
        if (N_pipe > 0)
        {
            if ((*pos) > 0)
                dup2(var_pipe[(*pos) - 1][0], STDIN_FILENO);
            if ((*pos) < N_pipe)
                dup2(var_pipe[(*pos)][1], STDOUT_FILENO);
            close_pipe(var_pipe, N_pipe, 1);
        }
        if (d->redirection_state[*pos] == RIGHT)
            redirect_right(d, pos, fd_out);
        else if (d->redirection_state[*pos] == RIGHT_RIGHT)
            redirect_right_right(d, pos, fd_out);
         else if (d->redirection_state[*pos] == LEFT)
            redirect_left(d, pos, fd_in);
        else if (d->redirection_state[*pos] == LEFT_LEFT)
            redirect_left_left(d, pos, fd_in);
        char *tmp_cmd = ft_strdup(ft_strjoin("/bin/", d->commands[*pos][0]));
        execve(tmp_cmd, d->commands[*pos], d->envp);
        exit(127);
    }
    else if (pid > 0)
        d->last_fork_pid = pid;    
}

void run_pipe_cmd(t_data *d, int N_pipe)
{
    int **var_pipe = malloc(sizeof(int *) * N_pipe);
    pid_t last_pid = -1;
    if (!var_pipe)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    alloc_error_pipe(N_pipe, var_pipe);
    int pos = 0;
    while (pos <= N_pipe)
    {
        if ((*d).cmd_state[pos] == CUSTOM)
            exec_custom_inpipe(var_pipe, d, N_pipe, &pos);
        else if ((*d).cmd_state[pos] == BUILT_IN)
            exec_built_inpipe(var_pipe, d, N_pipe, &pos);
        last_pid = d->last_fork_pid;
        pos++;
    }
    close_pipe(var_pipe, N_pipe, 0);

    int status;
    pid_t wpid;

    pos = 0;
    while ((wpid = wait(&status)) > 0)
    {
        if (wpid == last_pid)
        {
            if (WIFEXITED(status))
                d->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                d->exit_status = 128 + WTERMSIG(status);
        }
        pos++;
    }
}