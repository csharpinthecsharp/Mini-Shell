/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/06 20:08:46 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int select_type(t_data *d)
{
    d->cmd_count = count_cmds(d->commands);
    size_t i = 0;
    d->cmd_state = malloc(sizeof(int) * (d->cmd_count + 1));
    if (!d->cmd_state)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    while (i <= d->cmd_count)
    {
        int type = check_command(d->commands[i]);
        if (type == CUSTOM)
            d->cmd_state[i] = CUSTOM;
        else
        {
            if (is_valid_bin(d->commands[i][0]) == SUCCESS)
                d->cmd_state[i] = BUILT_IN;
            else
                print_error("command not found", d->commands[i][0]); 
        }
        i++;
    }
    pipe_the_pipe(d, pipe_count(d->input_splitted));
    return (SUCCESS);
}

void pipe_the_pipe(t_data *d, int N_pipe)
{
    // ALOCATE DOUBLE POINTEUR VAR PIPE
    int **var_pipe = malloc(sizeof(int *) * N_pipe);
    if (!var_pipe)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    // ALOCATE HIS COMPONENT
    int i = 0;
    while (i < N_pipe)
    {
        var_pipe[i] = malloc(sizeof(int) * 2); // * 2 -> [0] && [1]
        if (!var_pipe[i])
        {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        if (pipe(var_pipe[i]) == -1)
        {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    i = 0;
    while (i <= N_pipe)
    {
        // CUSTOM IN CMD HANDLE 
        if (d->cmd_state[i] == CUSTOM)
        {
            int saved_stdin = dup(STDIN_FILENO);
            int save_stdout = dup(STDOUT_FILENO);
            if (i > 0)
                dup2(var_pipe[i - 1][0], STDIN_FILENO);

            if (i < N_pipe)
                dup2(var_pipe[i][1], STDOUT_FILENO);
                
            close_pipe(var_pipe, N_pipe, 1);
            
            run_custom_cmd(d->commands[i], d);
            // on restore stdin/stdout
            dup2(saved_stdin, STDIN_FILENO);
            dup2(save_stdout, STDOUT_FILENO);
            close(saved_stdin);
            close(save_stdout);
        }
        // BUILT CMD HANDLE
        else
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                if (i > 0)
                    dup2(var_pipe[i - 1][0], STDIN_FILENO);

                if (i < N_pipe)
                    dup2(var_pipe[i][1], STDOUT_FILENO);

                close_pipe(var_pipe, N_pipe, 1);

                char *tmp_cmd = ft_strdup(ft_strjoin("/bin/", d->commands[i][0]));
                execve(tmp_cmd, d->commands[i], d->envp);
                free(tmp_cmd);
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
        }
        i++;
    }
    // Fermer les descripteurs dans le parent
    close_pipe(var_pipe, N_pipe, 0);
    // Attendre tous les enfants
    i = 0;
    while (i <= N_pipe)
    {
        wait(NULL);
        i++;
    }
}
