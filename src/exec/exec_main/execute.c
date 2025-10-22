/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:22:20 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/23 00:27:44 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void exec_alone_redir_inpipe(int **pipe, t_data *d, int n_pipe, int *pos)
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

void exec_custom_inpipe(int **pipe, t_data *d, int n_pipe, int *pos)
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

void exec_built_inpipe(int **pipe, t_data *d, int n_pipe, int *pos)
{
    pid_t   pid;

    handle_heredocs(d, pos);
    d->fd_out = 0;
    d->fd_in = 0;
    pid = fork();
    if (pid == 0)
    {
        handle_pipe(pipe, pos, n_pipe);
        handle_redirections(d, pos, &d->fd_out, &d->fd_in);
        handle_bin(&d->cmd[*pos], d);
        exit(127);
    }
    else if (pid > 0)
        d->last_fork_pid = pid;
    else
        perror("fork failed");
}

void execute_command_by_type(int **pipe, t_data *d, int n_pipe, int *pos)
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
