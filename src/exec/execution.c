/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/08 23:08:04 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#define NOT_FOUND 0
#define LEFT 1
#define RIGHT 2
#define LEFT_LEFT 3
#define RIGHT_RIGHT 4
#define ERROR 5
 
int select_type(t_data *d)
{
    size_t i = 0;
    alloc_cmd_state(d);

    while (i <= d->cmd_count)
    {
        if (is_redirect(d->commands[i] == NOT_FOUND)
            break;
        if (is_redirect(d->commands[i] = LEFT)  
            exec_redirect();
    }

    i = 0;
    while (i <= d->cmd_count)
    {
        int type = check_command(d->commands[i]);
        if (type == CUSTOM)
            (*d).cmd_state[i] = CUSTOM;
        else if (type == STATEFUL)
        {
            if (d->cmd_count == 0)
                run_custom_cmd(d->commands[i], d);
            else
                print_error("can't run in a pipe command", d->commands[i][0]);
        }
        else if (type == BUILT_IN)
        {
            if (is_valid_bin(d->commands[i][0]) == SUCCESS)
                (*d).cmd_state[i] = BUILT_IN;
            else
                print_error("command not found", d->commands[i][0]); 
        }
        i++;
    }
    run_pipe_cmd(d, pipe_count(d->input_splitted));
    return (SUCCESS);
}

void exec_redirect()

int is_redirect(char **argv)
{
    int i = 0;
    int count_left = 0;
    int count_right = 0;
    while (argv[i])
    {
        if (argv[i][0] == '>')
        {
            //*(tell_me_where) = i;
            count_right++;
        }
        else if argv[i][0] == '<')
            count_left++;
        i++;
    }
    if (count_left + count_right == 0)
        return (NOT_FOUND);
    else if (count_left == 1 && count_right == 0)
        return (LEFT);
    else if (count_left == 2 && count_right == 0)
        return (LEFT_LEFT);
    else if (count_left == 0 && count_right == 1)
        return (RIGHT);
    else if (count_left == 0 && count_right == 2)
        return (RIGHT_RIGHT);
    else
        return (ERROR);
}


static void exec_custom_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    if ((*d).cmd_state[*pos] == CUSTOM)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            if ((*pos) > 0)
                dup2(var_pipe[(*pos) - 1][0], STDIN_FILENO);
            if ((*pos) < N_pipe)
                dup2(var_pipe[(*pos)][1], STDOUT_FILENO);
            close_pipe(var_pipe, N_pipe, 1);
            run_custom_cmd(d->commands[(*pos)], d);
            exit(EXIT_SUCCESS);
        }
     }
}

static void exec_built_inpipe(int **var_pipe, t_data *d, int N_pipe, int *pos)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        if ((*pos) > 0)
            dup2(var_pipe[*pos - 1][0], STDIN_FILENO);
        if ((*pos) < N_pipe)
            dup2(var_pipe[*pos][1], STDOUT_FILENO);
        close_pipe(var_pipe, N_pipe, 1);
        char *tmp_cmd = ft_strdup(ft_strjoin("/bin/", d->commands[*pos][0]));
        execve(tmp_cmd, d->commands[*pos], d->envp);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
}

void run_pipe_cmd(t_data *d, int N_pipe)
{
    int **var_pipe = malloc(sizeof(int *) * N_pipe);
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
        pos++;
    }
    close_pipe(var_pipe, N_pipe, 0);
    pos = 0;
    while (pos <= N_pipe)
    {
        wait(NULL);
        pos++;
    }
}
