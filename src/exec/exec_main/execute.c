/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:22:20 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 15:05:49 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void handle_heredocs(t_data *d, int *pos)
{
    int i;

    i = 0;
    while (i < d->cmd[*pos].nb_redir)
    {
        if (d->cmd[*pos].arguments[i].state_redir == LEFT_LEFT)
            heredoc(d, pos, i);
        i++;
    }
}

static void handle_redirections(t_data *d, int *pos, int *fd_out, int *fd_in)
{
    int i;

    i = 0;
    while (i < d->cmd[*pos].nb_redir)
    {
        if (d->cmd[*pos].arguments[i].state_redir == RIGHT)
            redirect_right(d, pos, *fd_out, i);
        else if (d->cmd[*pos].arguments[i].state_redir == RIGHT_RIGHT)
            redirect_right_right(d, pos, *fd_out, i);
        else if (d->cmd[*pos].arguments[i].state_redir == LEFT)
            redirect_left(d, pos, *fd_in, i);
        i++;
    }
}

static void handle_pipe(int **pipe, int *pos, int n_pipe)
{
    if (n_pipe > 0)
    {
        if (*pos > 0)
            dup2(pipe[*pos - 1][0], STDIN_FILENO);
        if (*pos < n_pipe)
            dup2(pipe[*pos][1], STDOUT_FILENO);
        close_pipe(pipe, n_pipe, 1);
    }
}

static void exec_alone_redir_inpipe(int **pipe, t_data *d, int n_pipe, int *pos)
{
    pid_t   pid;

    handle_heredocs(d, pos);
    d->fd_out = 0;
    d->fd_in = 0;
    if (d->cmd[*pos].state_cmd == ALONE_REDIR &&
        (d->nb_cmd > 1 || d->cmd[*pos].nb_redir > 0))
    {
        pid = fork();
        if (pid == 0)
        {
            handle_pipe(pipe, pos, n_pipe);
            handle_redirections(d, pos, &d->fd_out, &d->fd_in);
            exit(d->exit_status);
        }
        else if (pid > 0)
            d->last_fork_pid = pid;
        else
            perror("fork failed");
    }
}

static void exec_custom_inpipe(int **pipe, t_data *d, int n_pipe, int *pos)
{
    pid_t   pid;

    handle_heredocs(d, pos);
    d->fd_out = 0;
    d->fd_in = 0;
    if (d->cmd[*pos].state_cmd == CUSTOM)
    {
        if (d->nb_cmd > 1 || d->cmd[*pos].nb_redir > 0)
        {
            pid = fork();
            if (pid == 0)
            {
                handle_pipe(pipe, pos, n_pipe);
                handle_redirections(d, pos, &d->fd_out, &d->fd_in);
                run_custom_cmd(d->cmd[*pos].arg, d);
                exit(d->exit_status);
            }
            else if (pid > 0)
                d->last_fork_pid = pid;
            else
                perror("fork failed");
        }
        else
            run_custom_cmd(d->cmd[*pos].arg, d);
    }
}

static void exec_built_inpipe(int **pipe, t_data *d, int n_pipe, int *pos)
{
    pid_t   pid;
    char    *tmp_cmd;

    handle_heredocs(d, pos);
    d->fd_out = 0;
    d->fd_in = 0;
    pid = fork();
    if (pid == 0)
    {
        handle_pipe(pipe, pos, n_pipe);
        handle_redirections(d, pos, &d->fd_out, &d->fd_in);
        if (ft_strncmp(d->cmd[*pos].arg[0], "/bin/", 5) == 0)
        {
            execve(d->cmd[*pos].arg[0], d->cmd[*pos].arg, d->envp);
            execve_error(d->cmd[*pos].arg[0]);
        }
        else if (d->cmd[*pos].arg[0])
        {
            tmp_cmd = ft_strjoin("/bin/", d->cmd[*pos].arg[0]);
            if (tmp_cmd)
            {
                execve(tmp_cmd, d->cmd[*pos].arg, d->envp);
                execve_error(tmp_cmd);
                free(tmp_cmd);
            }
        }
        exit(127);
    }
    else if (pid > 0)
        d->last_fork_pid = pid;
    else
        perror("fork failed");
}

static void restore_stdin(t_data *d)
{
    if (d->stdin_back != -1)
    {
        dup2(d->stdin_back, STDIN_FILENO);
        close(d->stdin_back);
        d->stdin_back = -1;
    }
}

static void handle_child_status(t_data *d, pid_t wpid, int status, pid_t last_pid)
{
    if (wpid == last_pid)
    {
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGPIPE)
        {
            print_error("Broken pipe", "!");
            d->exit_status = 1;
        }
        else if (WIFEXITED(status))
            d->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            d->exit_status = 128 + WTERMSIG(status);
    }
}

static void wait_for_children(t_data *d, pid_t last_pid)
{
    int     status;
    pid_t   wpid;

    while ((wpid = wait(&status)) > 0)
        handle_child_status(d, wpid, status, last_pid);
}

static void execute_command_by_type(int **pipe, t_data *d, int n_pipe, int *pos)
{
    if (check_output_ofeach(&d->cmd[*pos], d) == FAILED)
        exit(d->exit_status);
    if (d->cmd[*pos].state_cmd == CUSTOM)
        exec_custom_inpipe(pipe, d, n_pipe, pos);
    else if (d->cmd[*pos].state_cmd == BIN)
        exec_built_inpipe(pipe, d, n_pipe, pos);
    else if (d->cmd[*pos].state_cmd == ALONE_REDIR)
        exec_alone_redir_inpipe(pipe, d, n_pipe, pos);
}

void    start_execution(t_data *d)
{
    int     **pipe;
    int     pos;
    pid_t   last_pid;

    pipe = malloc(sizeof(int *) * (d->nb_cmd - 1));
    if (!pipe)
        perror("malloc failed");
    alloc_error_pipe(d->nb_cmd - 1, pipe);
    pos = 0;
    while (pos < d->nb_cmd)
    {
        execute_command_by_type(pipe, d, d->nb_cmd - 1, &pos);
        last_pid = d->last_fork_pid;
        pos++;
    }
    close_pipe(pipe, d->nb_cmd - 1, 0);
    wait_for_children(d, last_pid);
    restore_stdin(d);
}
