/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/21 16:01:55 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int start_execution(t_data *d)
{
    int is_stateful = 0;

    for (int i = 0; i < d->nb_cmd; i++) 
    {
        // printf("[DEBUG] Command %d: nb_arg=%d\n", i, d->cmd[i].nb_arg);

        // 1. Count redirections
        int nb_redir = count_redir(d->cmd[i].arg);
        d->cmd[i].nb_redir = nb_redir;
        // printf("[DEBUG] -> count_redir found %d redirections\n", nb_redir);

        // 2. Allocate arguments[]
        if (nb_redir > 0) 
        {
            d->cmd[i].arguments = calloc(nb_redir, sizeof *d->cmd[i].arguments);
            if (!d->cmd[i].arguments)
                return FAILED;
            // printf("[DEBUG] -> allocated arguments[%d]\n", nb_redir);
        } 
        else 
        {
            d->cmd[i].arguments = NULL;
            // printf("[DEBUG] -> no redirections, arguments=NULL\n");
        }

        // 3. Fill arguments[]
        if (nb_redir > 0)
        {
            int k = 0;
            for (int j = 0; j < d->cmd[i].nb_arg; j++) 
            {
                if (put_redir(d, i, j, k)) {
                    // printf("[DEBUG] put_redir: arg[%d]=\"%s\" -> redir[%d] type=%d file=\"%s\"\n",
                    //     j,
                    //     d->cmd[i].arg[j],
                    //     k,
                    //     d->cmd[i].arguments[k].state_redir,
                    //     d->cmd[i].arguments[k].file);
                    k++;
                }
            }
            d->cmd[i].nb_redir = k;
            // printf("[DEBUG] -> final nb_redir=%d\n", k);
        }

        // 4. Clean argv
        if (d->cmd[i].nb_redir > 0) 
        {
            // printf("[DEBUG] Cleaning argv for command %d\n", i);
            char **old = d->cmd[i].arg;
            char **clean = fix_redir_arg(&d->cmd[i]);

            // free each string in old argv
            for (int j = 0; old[j]; j++) {
                // printf("[DEBUG] freeing old arg[%d]=\"%s\"\n", j, old[j]);
                free(old[j]);
            }
            free(old);

            d->cmd[i].arg = clean;

            // print cleaned argv
            for (int j = 0; d->cmd[i].arg[j]; j++) {
                // printf("[DEBUG] cleaned arg[%d]=\"%s\"\n", j, d->cmd[i].arg[j]);
            }
        }

        // 5. Check emptiness and state
        if (is_empty(d, i, 0) == FAILED) {
            // printf("[DEBUG] Command %d is empty after cleaning\n", i);
            return FAILED;
        }
        int type = check_command(d->cmd[i].arg, d);
        // printf("[DEBUG] check_command returned type=%d\n", type);
        if (put_cmdstate(type, &is_stateful, &d->cmd[i], d) == FAILED) {
            // printf("[DEBUG] put_cmdstate failed for command %d\n", i);
            return FAILED;
        }
    }

    if (is_stateful == 0) {
        // printf("[DEBUG] No stateful command, running non-stateful pipeline\n");
        run_non_stateful(d);
    }

    return SUCCESS;
}




static void exec_alone_redir_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    int i = 0;
    while (i < d->cmd[*pos].nb_redir)
    {
        if (d->cmd[*pos].arguments[i].state_redir == LEFT_LEFT)
            heredoc(d, pos, i);
        i++;
    }
    
    i = 0;
    int fd_out = 0;
    int fd_in = 0;
    if (d->cmd[*pos].state_cmd == ALONE_REDIR)
    {
        if (d->nb_cmd > 1 || d->cmd[*pos].nb_redir > 0)
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
                
                int i = 0;
                while (d->cmd[*pos].arguments[i].state_redir)
                {
                    if (d->cmd[*pos].arguments[i].state_redir == RIGHT)
                        redirect_right(d, pos, fd_out, i);
                    else if (d->cmd[*pos].arguments[i].state_redir == RIGHT_RIGHT)
                        redirect_right_right(d, pos, fd_out, i);
                    else if (d->cmd[*pos].arguments[i].state_redir == LEFT)
                        redirect_left(d, pos, fd_in, i);
                    i++;
                } 
                exit(d->exit_status);
            }
            else if (pid > 0)
                d->last_fork_pid = pid;
            else
            {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
        }
    }
}

static void exec_custom_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    int i = 0;
    while (i < d->cmd[*pos].nb_redir)
    {
        if (d->cmd[*pos].arguments[i].state_redir == LEFT_LEFT)
            heredoc(d, pos, i);
        i++;
    }
    
    i = 0;
    int fd_out = 0;
    int fd_in = 0;
    if (d->cmd[*pos].state_cmd == CUSTOM)
    {
        if (d->nb_cmd > 1 || d->cmd[*pos].nb_redir > 0)
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
                
                int i = 0;
                while (i < d->cmd[*pos].nb_redir)
                {
                    if (d->cmd[*pos].arguments[i].state_redir == RIGHT)
                        redirect_right(d, pos, fd_out, i);
                    else if (d->cmd[*pos].arguments[i].state_redir == RIGHT_RIGHT)
                        redirect_right_right(d, pos, fd_out, i);
                    else if (d->cmd[*pos].arguments[i].state_redir == LEFT)
                        redirect_left(d, pos, fd_in, i);
                    i++;
                }
                    
                run_custom_cmd(d->cmd[*pos].arg, d);
                exit(d->exit_status);
            }
            else if (pid > 0)
                d->last_fork_pid = pid;
            else
            {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
        }
        else
            run_custom_cmd(d->cmd[*pos].arg, d);
    }
}
static void execve_error(char *cmd)
{
    if (errno == ENOENT)
        print_error("Command or file not found", cmd);
    else if (errno == EACCES)
        print_error("Permission denied", cmd);
    else if (errno == ENOMEM)
        print_error("Not enough memory", cmd);
    else if (errno == EFAULT)
        print_error("Invalid pointer", cmd);
    else if (errno == EINVAL)
        print_error("Invalid argument", cmd);
    else if (errno == ENOTDIR)
        print_error("A path component is not a directory", cmd);
    else
        print_error("Execution failed", cmd);
}
static void exec_built_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    int i = 0;
    while (i < d->cmd[*pos].nb_redir)
    {
        if (d->cmd[*pos].arguments[i].state_redir == LEFT_LEFT)
            heredoc(d, pos, i);
        i++;
    }
    
    i = 0;
    int fd_out = 0;
    int fd_in = 0;
    pid_t pid = fork();
    if (pid == 0)
    {
        if (d->nb_cmd > 1)
        {
            if ((*pos) > 0)
                dup2(var_pipe[(*pos) - 1][0], STDIN_FILENO);
            if ((*pos) < N_pipe)
                dup2(var_pipe[(*pos)][1], STDOUT_FILENO);
            close_pipe(var_pipe, N_pipe, 1);
        }
        
        int i = 0;
        while (i < d->cmd[*pos].nb_redir)
        {
            if (d->cmd[*pos].arguments[i].state_redir == RIGHT)
                redirect_right(d, pos, fd_out, i);
            else if (d->cmd[*pos].arguments[i].state_redir == RIGHT_RIGHT)
                redirect_right_right(d, pos, fd_out, i);
            else if (d->cmd[*pos].arguments[i].state_redir == LEFT)
                redirect_left(d, pos, fd_in, i);
            i++;
        }
        
        if (ft_strncmp(d->cmd[*pos].arg[0], "/bin/", 5) == 0)
        {
            execve(d->cmd[*pos].arg[0], d->cmd[*pos].arg, d->envp);
            execve_error(d->cmd[*pos].arg[0]);
        }
        else if (d->cmd[*pos].arg[0])
        {
            char *tmp_cmd = ft_strdup(ft_strjoin("/bin/", d->cmd[*pos].arg[0]));
            if (tmp_cmd) {
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
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
}

void run_non_stateful(t_data *d)
{
    int **var_pipe = malloc(sizeof(int *) * (d->nb_cmd - 1));
    pid_t last_pid = -1;
    if (!var_pipe)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    alloc_error_pipe(d->nb_cmd - 1, var_pipe);
    int pos = 0;
    while (pos < d->nb_cmd)
    {
        if (check_output_ofeach(&d->cmd[pos], d) == FAILED)
            exit(d->exit_status);
        if (d->cmd[pos].state_cmd == CUSTOM)
            exec_custom_inpipe(var_pipe, d, d->nb_cmd - 1, &pos);
        else if (d->cmd[pos].state_cmd == BIN)
            exec_built_inpipe(var_pipe, d, d->nb_cmd - 1, &pos);
        else if (d->cmd[pos].state_cmd == ALONE_REDIR)
            exec_alone_redir_inpipe(var_pipe, d, d->nb_cmd - 1, &pos);
        last_pid = d->last_fork_pid;
        pos++;
    }
    close_pipe(var_pipe, d->nb_cmd - 1, 0);
    int status;
    pid_t wpid;
    pos = 0;
    while ((wpid = wait(&status)) > 0)
    {
        if (wpid == last_pid)
        {
            if (WIFSIGNALED(status) && WTERMSIG(status) == SIGPIPE)
            {
                print_error("Broken pipe", "!");
                d->exit_status = 1;
            }
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