/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/28 14:51:56 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// REPL 
// R = READ | E = EVALUATE | P = EXECUTE | L = LOOP.
int main(int ac, char *av[], char *envp[])
{
    if (ac != 1)
        return (EXIT_FAILURE);
    (void)av;
    
    char buffer[BUFFER_SIZE];
    char *path;
    char *input;
    pid_t pid;
    
    printf(TEMPLATE_SETUP_SCREEN);
    
    while (1)
    {
        path = getpath(buffer);

        input = readline(TEMPLATE_PROMPT);
        free(path);
        
        // Si EOF on sors de la boucle.
        // EOF = CTRL D.
        if (!input)
        {
            printf(TEMPLATE_GOOD_BYE);
            exit(EXIT_SUCCESS);
        }
        // Parent
        // └── fork()
        //      ├── Enfant → execve("ls") → remplace par /bin/ls
        //      │             ↳ si erreur → perror + exit
        //      └── Parent → wait(NULL) → attend la fin de l’enfant
        if (ft_strncmp(input, "ls", 2) == 0)
        {
            pid = fork();
            if (pid == 0)
            {
                char *ls_path[] = {"/bin/ls", NULL};
                execve(ls_path[0], ls_path, envp);
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
            else
                wait(NULL);
        }
        // Ajouter a l'historique.
        add_history(input);
        
        free(input);
    }
    return (EXIT_SUCCESS);
}

