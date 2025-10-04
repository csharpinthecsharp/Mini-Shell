/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:52:18 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/04 21:46:48 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define N_proc 2
#define N_desc 2
void pipe_the_pipe(char ***commands, char **envp, int N_pipe)
{
    int **var_pipe;
    int i = 0;
    var_pipe = malloc(sizeof(int*) * N_pipe);
    while (i < N_pipe)
    {
        var_pipe[i] = malloc(sizeof(int) * N_desc);
        i++;
    }
    
    i = 0;
    while (i <= N_pipe)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork failed.");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            // STDIN si ce n'est pas la premiere commande.
            if (i > 0)
                dup2(var_pipe[i - 1][0], STDIN_FILENO);
            // STDOUT si ce n'est pas la derniere commande.
            if (i < N_pipe)
                dup2(var_pipe[i][1], STDOUT_FILENO);
            // on close
            int j = 0;
            while (j < N_pipe)
            {
                close(var_pipe[j][0]);
                close(var_pipe[j][1]);
                j++;
            }
            while (j < N_pipe)
            {
                free(var_pipe[j]);
                j++;
            }
            free(var_pipe);
            execve(commands[i][0], commands[i], envp);
            perror("execve failed");
        }
        else
            wait(NULL);
        if (i < N_pipe)
        {
            close(var_pipe[i][0]);
            close(var_pipe[i][1]);
        }
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
