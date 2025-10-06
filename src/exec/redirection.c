/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:25:36 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/06 14:38:32 by ltrillar         ###   ########.fr       */
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
    return (SUCCESS);
}

static size_t count_cmds(t_data *d)
{
    d->cmd_count = 0;
    while (d->commands[d->cmd_count])
        d->cmd_count++;
    return (d->cmd_count);
}

int select_type(t_data *d)
{
    count_cmds(d);
    size_t i = 0;
    while (i <= d->cmd_count)
    {
        if (check_command(d->commands[i]) == CUSTOM)
        {
            d->cmd_state[i] = CUSTOM;
        }
        else if (check_command(d->commands[i]) == BUILT_IN)
        {
            if (is_valid_bin(d->commands[i][0]) == SUCCESS)
            {
                d->cmd_state[i] = BUILT_IN;
            }
            else
                print_error("command not found", d->commands[i][0]);
        }
        pipe_the_pipe(d, pipe_count(d->input_splitted));
        i++;
    }
    return (SUCCESS);
}

void pipe_the_pipe(t_data *d, int N_pipe)
{
    int **var_pipe = malloc(sizeof(int *) * N_pipe);
    if (!var_pipe)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
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
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Redirection STDIN
            if (i > 0)
                dup2(var_pipe[i - 1][0], STDIN_FILENO);

            // Redirection STDOUT
            if (i < N_pipe)
                dup2(var_pipe[i][1], STDOUT_FILENO);

            // Fermer tous les descripteurs inutiles*
            int j = 0;
            while (j < N_pipe)
            {
                close(var_pipe[j][0]);
                close(var_pipe[j][1]);
                j++;
            }

            if (d->cmd_state[i] == BUILT_IN)
            {
                run_build_cmd(d);
                execve(d->commands[i][0], d->commands[i], d->envp);
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
            else if (d->cmd_state[i] == CUSTOM)
            {
                run_custom_cmd(d);
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

    //pipe[0] = read;
    //pipe[1] = write;

    // CREER N PIPES POUR N COMMANDES
    // CREER N PROCESSUS AVEC FORK()
    // REDIRIGER LES ENTREES/SORTIES AVEC DUP2()
        // chaque commandes lit depuis le pipe precedents et,
        // ecrit dans le pipe suivant.
    // FERMER LES DESCRIPTEURS INUTILES DANS CHAQUE PROCESSUS
    // EXECVP
}
