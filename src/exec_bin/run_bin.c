/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:52:18 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/05 02:07:38 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#define N_proc 2
#define N_desc 2
void pipe_the_pipe(char ***commands, char **envp, int N_pipe)
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
        var_pipe[i] = malloc(sizeof(int) * N_desc);
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

            execve(commands[i][0], commands[i], envp);
            perror("execve failed");
            exit(EXIT_FAILURE);
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
