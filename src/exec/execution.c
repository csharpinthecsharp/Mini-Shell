/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/15 15:54:18 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int start_execution(t_data *d)
{
    int i;
    int is_stateful;

    i = 0;
    is_stateful = 0;
    alloc_start_execution(d);
    while (i <= d->cmd_count)
    {
        if (is_empty(i, d) == 1)
            return (FAILED);
        int type = check_command(d->commands[i]);
        int redir_type = is_redirect(d->commands[i], d);
        put_cmdstate(type, &i, &is_stateful, d);
        if ((redir_type > NOT_FOUND))
        {
            (*d).redirection_state[i] = redir_type;
            d->commands[i] = fix_redir_arg(d, d->commands[i], redir_type, i);
            if (is_empty(i, d) == 1)
                return (FAILED);
        }
        else
            (*d).redirection_state[i] = 0;
        i++;
    }
    if (is_stateful == 0)
        run_non_stateful(d, d->cmd_count);
    return (SUCCESS);
}

static void exec_custom_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    if (d->redirection_state[*pos] == LEFT_LEFT)
        heredoc(d, pos);
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
    if (d->redirection_state[*pos] == LEFT_LEFT)
        heredoc(d, pos);
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
        
        if (ft_strncmp(d->commands[*pos][0], "/bin/", 5) == 0)
            execve(d->commands[*pos][0], d->commands[*pos], d->envp);
        else
        {
            char *tmp_cmd = ft_strdup(ft_strjoin("/bin/", d->commands[*pos][0]));
            execve(tmp_cmd, d->commands[*pos], d->envp);
        }
        exit(127);
    }
    else if (pid > 0)
        d->last_fork_pid = pid;
}

void run_non_stateful(t_data *d, int N_pipe)
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
        else if ((*d).cmd_state[pos] == BIN)
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
    
    if (d->stdin_back != -1)
    {
        dup2(d->stdin_back, STDIN_FILENO);
        close(d->stdin_back);
        d->stdin_back = -1;
    }
}