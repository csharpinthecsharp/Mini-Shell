/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:18:23 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/27 21:22:46 by ltrillar         ###   ########.fr       */
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
    
    while (1)
    {
        path = getpath(buffer);
        
        input = readline(path);
        free(path);
        
        // Si EOF on sors de la boucle.
        if (!input)
            break;
        

        // Parent
        // └── fork()
        //      ├── Enfant → execve("ls") → remplace par /bin/ls
        //      │             ↳ si erreur → perror + exit
        //      └── Parent → wait(NULL) → attend la fin de l’enfant
        pid_t pid;
        pid = fork();
        if (pid == 0)
        {
            if (ft_strncmp(input, "ls", 6) == 0)
            {
                char *ls_path[] = {"/bin/ls", NULL};
                execve(ls_path[0], ls_path, envp);
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
        }
        else
            wait(NULL);

        // Ajouter a l'historique.
        add_history(input);
        
        free(input);
    }
    return (EXIT_SUCCESS);
}