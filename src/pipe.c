/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:52:18 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/04 14:50:52 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define N_pipe
#define N_proc
#define N_desc 2
void pipe_the_pipe()
{
    int *pipe = malloc(sizeof(int) * N_desc * N_pipe);
    if (!pipe)
        return ;
    

    pipe[N_pipe][2];

    int i = 0;
    while (i <= N_pipe)
    {
        pid_t pid = fork();
        if (pid == 0)
        else
            wait(NULL);
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