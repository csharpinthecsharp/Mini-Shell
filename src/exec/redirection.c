/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/06 18:31:45 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#define BUILT_IN 0
#define CUSTOM 1
int check_command(char **argv)
{
    int len = ft_strlen(argv[0]);
    if (ft_strncmp(argv[0], "pwd", len) == 0)
        return (CUSTOM);
    else if (ft_strncmp(argv[0], "exit", len) == 0)
        return (CUSTOM);
    else if (ft_strncmp(argv[0], "echo", len) == 0)
        return (CUSTOM);
    else if (ft_strncmp(argv[0], "cd", len) == 0)
        return (CUSTOM);
    else if (ft_strncmp(argv[0], "export", len) == 0)
        return (CUSTOM);
    return (BUILT_IN);
}

static int is_valid_bin(char *str)
{
    char *bin = ft_strdup(ft_strjoin("/bin/", str));
    int fd = open(bin, O_RDONLY);
    if (fd < 0)
        return (FAILED);
    close(fd);
    return (SUCCESS);
}

static size_t count_cmds(char ***cmds)
{
    size_t i = 0;
    while (cmds[i])
        i++;
    return (i - 1);
}

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
                
            int j = 0; 
            while (j < N_pipe)
            {
                close(var_pipe[j][0]);
                close(var_pipe[j][1]);
                j++;
            }
            
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

                int j = 0;
                while (j < N_pipe)
                {
                    close(var_pipe[j][0]);
                    close(var_pipe[j][1]);
                    j++;
                }
                
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
    i = 0;
    while (i < N_pipe)
    {
        close(var_pipe[i][0]);
        close(var_pipe[i][1]);
        free(var_pipe[i]);
        i++;
    }
    free(var_pipe);

    // Attendre tous les enfants
    i = 0;
    while (i <= N_pipe)
    {
        wait(NULL);
        i++;
    }
}
