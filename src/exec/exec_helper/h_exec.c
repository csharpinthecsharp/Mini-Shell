/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:48:56 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/22 15:34:39 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void handle_heredocs(t_data *d, int *pos)
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

void handle_bin(t_cmd *cmd, t_data *d)
{
    char    *tmp_cmd;
    if (ft_strncmp(cmd->arg[0], "/bin/", 5) == 0)
    {
        execve(cmd->arg[0], cmd->arg, d->envp);
        execve_error(cmd->arg[0]);
    }
    else if (cmd->arg[0])
    {
        tmp_cmd = ft_strjoin("/bin/", cmd->arg[0]);
        if (tmp_cmd)
        {
            execve(tmp_cmd, cmd->arg, d->envp);
            execve_error(tmp_cmd);
            free(tmp_cmd);
        }
    }
}

void handle_redirections(t_data *d, int *pos, int *fd_out, int *fd_in)
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

void handle_pipe(int **pipe, int *pos, int n_pipe)
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


void handle_child_status(t_data *d, pid_t wpid, int status, pid_t last_pid)
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

void wait_for_children(t_data *d, pid_t last_pid)
{
    int     status;
    pid_t   wpid;

    while ((wpid = wait(&status)) > 0)
        handle_child_status(d, wpid, status, last_pid);
}

void restore_stdin(t_data *d)
{
    if (d->stdin_back != -1)
    {
        dup2(d->stdin_back, STDIN_FILENO);
        close(d->stdin_back);
        d->stdin_back = -1;
    }
}

void close_pipe(int **var_pipe, int N_pipe, int state)
{
    int i = 0; 
    while (i < N_pipe)
    {
        close(var_pipe[i][0]);
        close(var_pipe[i][1]);
        if (state != 1)
            free(var_pipe[i]);
        i++;
    }
    if (state != 1)
        free(var_pipe);
}